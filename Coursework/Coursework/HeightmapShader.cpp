// tessellation shader.cpp
#include "HeightmapShader.h"


HeightmapShader::HeightmapShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"heightmap_vs.cso", L"heightmap_hs.cso", L"heightmap_ds.cso", L"heightmap_ps.cso");
}


HeightmapShader::~HeightmapShader()
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

void HeightmapShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
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
	heightmapBufferDesc.ByteWidth = sizeof(HeightMapBufferType);
	heightmapBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	heightmapBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	heightmapBufferDesc.MiscFlags = 0;
	heightmapBufferDesc.StructureByteStride = 0;


	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heighMapBuffer);


	D3D11_BUFFER_DESC lightBufferDesc;
	// Setup light buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);

}

void HeightmapShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
}


void HeightmapShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	XMFLOAT4 EdgeTesellation, XMFLOAT2 InsideTesellation, ID3D11ShaderResourceView* texture, XMFLOAT3 CameraPosInput, float InputAmplitude, ID3D11ShaderResourceView* heightmapTexture,
	Light* light[])
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
	result = deviceContext->Map(heighMapBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HeightMapBufferType* heightPtr = (HeightMapBufferType*)mappedResource.pData;
	heightPtr->padding = XMFLOAT3(0.0f,0.0f,0.0f);
	heightPtr->amplitude = InputAmplitude;
	deviceContext->Unmap(heighMapBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &heighMapBuffer);
	deviceContext->DSSetShaderResources(0, 1, &heightmapTexture);


	//Additional
	// Send light data to pixel shader
	LightBufferType* lightPtr;
	deviceContext->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//Light1
	lightPtr = (LightBufferType*)mappedResource.pData;

	for (int i = 0; i < 3; i++)
	{
		lightPtr->ambient[i] = light[i]->getAmbientColour();
		lightPtr->diffuse[i] = light[i]->getDiffuseColour();
		lightPtr->position[i] = XMFLOAT4(light[i]->getPosition().x, light[i]->getPosition().y, light[i]->getPosition().z, 0.0f);
		lightPtr->direction[i] = XMFLOAT4(light[i]->getDirection().x, light[i]->getDirection().y, light[i]->getDirection().z, 0.0f);
		lightPtr->attenuation[i] = XMFLOAT4(light[i]->getAttenuationFactors().x, light[i]->getAttenuationFactors().y, light[i]->getAttenuationFactors().z, 0.0f);

	}
	deviceContext->Unmap(lightBuffer, 0);

	deviceContext->PSSetConstantBuffers(0, 1, &lightBuffer);
	deviceContext->PSSetShaderResources(0, 1, &texture);
	deviceContext->PSSetSamplers(0, 1, &sampleState);

}


