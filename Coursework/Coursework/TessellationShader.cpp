// tessellation shader.cpp
#include "tessellationshader.h"


TessellationShader::TessellationShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"tessellation_vs.cso", L"tessellation_hs.cso", L"tessellation_ds.cso", L"tessellation_ps.cso");
}


TessellationShader::~TessellationShader()
{
	if (sampleState)
	{
		sampleState->Release();
		sampleState = 0;
	}
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}
	if (layout)
	{
		layout->Release();
		layout = 0;
	}
	
	//Release base shader components
	BaseShader::~BaseShader();
}

void TessellationShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC hullBufferDesc;
	hullBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	hullBufferDesc.ByteWidth = sizeof(HullBufferType);
	hullBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hullBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	hullBufferDesc.MiscFlags = 0;
	hullBufferDesc.StructureByteStride = 0;


	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);



	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC cameraBufferDesc;
	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;


	renderer->CreateBuffer(&cameraBufferDesc, NULL, &cameraBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC heightmapBufferDesc;
	heightmapBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	heightmapBufferDesc.ByteWidth = sizeof(SeaBufferType);
	heightmapBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	heightmapBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	heightmapBufferDesc.MiscFlags = 0;
	heightmapBufferDesc.StructureByteStride = 0;


	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &SeaBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC waterBufferDesc;
	waterBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	waterBufferDesc.ByteWidth = sizeof(WaterBufferType);
	waterBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	waterBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	waterBufferDesc.MiscFlags = 0;
	waterBufferDesc.StructureByteStride = 0;
	
	renderer->CreateBuffer(&waterBufferDesc, NULL, &WaterBuffer);


}

void TessellationShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
}


void TessellationShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	XMFLOAT4 EdgeTesellation, XMFLOAT2 InsideTesellation, XMFLOAT3 CameraPosInput, XMFLOAT4 InputWaveSettings[], ID3D11ShaderResourceView* texture,
	float InputWaveDirection[], float time, float waterOffset,float depthScalar, float Sealevel, float amplitude)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(worldMatrix);
	XMMATRIX tview = XMMatrixTranspose(viewMatrix);
	XMMATRIX tproj = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->DSSetConstantBuffers(0, 1, &matrixBuffer);


	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HullBufferType* HullPtr = (HullBufferType*)mappedResource.pData;
	HullPtr->Edges = EdgeTesellation;
	HullPtr->Inside = InsideTesellation;
	HullPtr->padding = XMFLOAT2(0.0f, 0.0f);
	deviceContext->Unmap(hullBuffer, 0);
	deviceContext->HSSetConstantBuffers(0,1,&hullBuffer);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CameraBufferType* CamPtr = (CameraBufferType*)mappedResource.pData;
	CamPtr->cameraPosition = CameraPosInput;
	CamPtr->padding = 1.0f;
	deviceContext->Unmap(cameraBuffer, 0);
	deviceContext->HSSetConstantBuffers(1, 1, &cameraBuffer);


	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(SeaBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	SeaBufferType* heightPtr = (SeaBufferType*)mappedResource.pData;

	for (int i = 0; i < 3; i++)
	{
		heightPtr->WaveSettings[i] = InputWaveSettings[i];
		heightPtr->WaveDirectionTimePadding[i] = XMFLOAT4(InputWaveDirection[i], time, 1.f, 1.f);

	}
	deviceContext->Unmap(SeaBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &SeaBuffer);

	result = deviceContext->Map(WaterBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	WaterBufferType* waterPtr = (WaterBufferType*)mappedResource.pData;
	waterPtr->depthScalar = depthScalar;
	waterPtr->heightmapAmplitude = amplitude;
	waterPtr->offsett = waterOffset;
	waterPtr->waterPlaneHeight = Sealevel;

	deviceContext->Unmap(WaterBuffer, 0);


	
	
	

	deviceContext->PSSetConstantBuffers(0, 1, &WaterBuffer);

	deviceContext->PSSetShaderResources(0, 1, &texture);


	




}


