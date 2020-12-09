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
	D3D11_BUFFER_DESC matrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(MatrixBufferType));
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC hullBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HullBufferType));
	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);



	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC cameraBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(CameraBufferType));
	renderer->CreateBuffer(&cameraBufferDesc, NULL, &cameraBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC SeaBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(SeaBufferType));
	renderer->CreateBuffer(&SeaBufferDesc, NULL, &SeaBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC waterBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(WaterBufferType));
	renderer->CreateBuffer(&waterBufferDesc, NULL, &WaterBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC waterColorBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(WaterColorBufferType));
	renderer->CreateBuffer(&waterColorBufferDesc, NULL, &WaterColorBuffer);



}

void TessellationShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
}

void TessellationShader::setHullShaderParameters(ID3D11DeviceContext* deviceContext, float tessellationFactor, float dynamicTessellationFactor, bool dynmaicTesellationToggle, float distanceScalar)
{

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HullBufferType* HullPtr = (HullBufferType*)mappedResource.pData;
	HullPtr->distanceScalar = distanceScalar;
	HullPtr->dynamicTessellationFactor = dynamicTessellationFactor;
	HullPtr->dynmaicTesellationToggle = dynmaicTesellationToggle;
	HullPtr->tessellationFactor = tessellationFactor;
	deviceContext->Unmap(hullBuffer, 0);
	deviceContext->HSSetConstantBuffers(0, 1, &hullBuffer);
}

void TessellationShader::setPixelShaderParameters(ID3D11DeviceContext* deviceContext, float waterOffset, float depthScalar, float Sealevel, float amplitude, float deepColor[4],
	float shallowColor[4], ID3D11ShaderResourceView* heightTexture)
{
	result = deviceContext->Map(WaterBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	WaterBufferType* waterPtr = (WaterBufferType*)mappedResource.pData;

	waterPtr->heightmapAmplitude = amplitude;
	waterPtr->waterPlaneHeight = Sealevel;
	waterPtr->offsett = waterOffset;
	waterPtr->depthScalar = depthScalar;

	deviceContext->Unmap(WaterBuffer, 0);


	result = deviceContext->Map(WaterColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	WaterColorBufferType* waterColorPtr = (WaterColorBufferType*)mappedResource.pData;

	waterColorPtr->deepColor = XMFLOAT4(deepColor[0], deepColor[1], deepColor[2], deepColor[3]);
	waterColorPtr->shallowColor = XMFLOAT4(shallowColor[0], shallowColor[1], shallowColor[2], shallowColor[3]);
	
	deviceContext->Unmap(WaterColorBuffer, 0);


	deviceContext->PSSetConstantBuffers(1, 1, &WaterBuffer);
	deviceContext->PSSetConstantBuffers(2, 1, &WaterColorBuffer);

	deviceContext->PSSetShaderResources(1, 1, &heightTexture);
}



void TessellationShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	XMFLOAT4 EdgeTesellation, XMFLOAT2 InsideTesellation, XMFLOAT3 CameraPosInput, XMFLOAT4 InputWaveSettings[],
	float InputWaveDirection[], float time)
{
	

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

	

}


