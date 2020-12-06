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

	//Sampler for normal textures
	D3D11_SAMPLER_DESC samplerDesc = BufferHelpers::CreateSamplerDescription();
	renderer->CreateSamplerState(&samplerDesc, &sampleState);

	//Sampler for DepthMaps
	D3D11_SAMPLER_DESC shadowSamplerDesc = BufferHelpers::CreateShadowSamplerDescription();
	renderer->CreateSamplerState(&samplerDesc, &sampleStateShadow);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(MatrixBufferType));
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC lightMatrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(LightMatrixBufferType));
	renderer->CreateBuffer(&lightMatrixBufferDesc, NULL, &lightMatrixBuffer);
	

	// Setup the description of the dynamic matrix constant buffer that is in the hull shader.
	D3D11_BUFFER_DESC hullBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HullBufferType));
	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);



	// Setup the description of the dynamic matrix constant buffer that is in the hull shader.
	D3D11_BUFFER_DESC cameraBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(CameraBufferType));

	renderer->CreateBuffer(&cameraBufferDesc, NULL, &cameraBuffer);

	// Setup the description of the dynamic constant buffer that is in the domain shader.
	//Creates a default buffer description using bytewith provided
	D3D11_BUFFER_DESC heightmapBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HeightMapBufferType));

	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heighMapBuffer);

	// Setup light buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC lightBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(DirectionalLightBufferType));
	
	renderer->CreateBuffer(&lightBufferDesc, NULL, &dirLightBuffer);

	//Setup pointlight buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC pointLightDesc = BufferHelpers::CreateBufferDescription(sizeof(PointlightBufferType));
	renderer->CreateBuffer(&pointLightDesc, NULL, &pointLightBuffer);



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
	XMFLOAT4 TessellationFactor, ID3D11ShaderResourceView* texture, XMFLOAT3 CameraPosInput, float InputAmplitude, ID3D11ShaderResourceView* heightmapTexture, Light* directionalLight,
	Light* pointlight[], ID3D11ShaderResourceView* directionalDepthTex, ID3D11ShaderResourceView* pointDepthTex[], XMMATRIX pointlightViewMatrix[])
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(worldMatrix);
	XMMATRIX tview = XMMatrixTranspose(viewMatrix);
	XMMATRIX tproj = XMMatrixTranspose(projectionMatrix);

	//Domain buffers
	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	MatrixBufferType* matrixPtr = (MatrixBufferType*)mappedResource.pData;
	matrixPtr->world = tworld;// worldMatrix;
	matrixPtr->view = tview;
	matrixPtr->projection = tproj;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->DSSetConstantBuffers(0, 1, &matrixBuffer);

	//Hull buffers
	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HullBufferType* HullPtr = (HullBufferType*)mappedResource.pData;
	HullPtr->TessellationFactor = TessellationFactor;
	deviceContext->Unmap(hullBuffer, 0);
	deviceContext->HSSetConstantBuffers(0,1,&hullBuffer);


	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CameraBufferType* CamPtr = (CameraBufferType*)mappedResource.pData;
	CamPtr->cameraPosition = CameraPosInput;
	CamPtr->padding = 1.0f;
	deviceContext->Unmap(cameraBuffer, 0);
	deviceContext->HSSetConstantBuffers(1, 1, &cameraBuffer);

	//Pixel Buffers
	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(heighMapBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HeightMapBufferType* heightPtr = (HeightMapBufferType*)mappedResource.pData;
	heightPtr->padding = XMFLOAT3(0.0f,0.0f,0.0f);
	heightPtr->amplitude = InputAmplitude;
	deviceContext->Unmap(heighMapBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &heighMapBuffer);
	deviceContext->DSSetShaderResources(0, 1, &heightmapTexture);


	// Send light data to pixel shader
	DirectionalLightBufferType* dirLightPtr;
	deviceContext->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	dirLightPtr = (DirectionalLightBufferType*)mappedResource.pData;
	dirLightPtr->ambient = directionalLight->getAmbientColour();
	dirLightPtr->diffuse = directionalLight->getDiffuseColour();
	
	deviceContext->Unmap(dirLightBuffer, 0);

	//Set pointlight light buffer
	PointlightBufferType* pointlightPtr;
	deviceContext->Map(pointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	pointlightPtr = (PointlightBufferType*)mappedResource.pData;

	//Set buffer data
	for (size_t i = 0; i < numberOfPointlights; i++)
	{
		//Set diffuse color.
		pointlightPtr->diffuse[i] = pointlight[i]->getDiffuseColour();
		// Set buffer pointer with pointlight position -->  Note: I hate that I can't do getPosition().xyz, makes line too long.
		pointlightPtr->position[i] = XMFLOAT4(pointlight[i]->getPosition().x, pointlight[i]->getPosition().y, pointlight[i]->getPosition().z,1);
	}
	
	deviceContext->Unmap(pointLightBuffer, 0);


	//Set pointlight light buffer
	LightMatrixBufferType* lightMatrixPtr;
	deviceContext->Map(lightMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightMatrixPtr = (LightMatrixBufferType*)mappedResource.pData;

	//Directional Light
	//Get orthomatrix
	lightMatrixPtr->dirLightProjection = directionalLight->getOrthoMatrix();
	//Need to update view matrix
	directionalLight->generateViewMatrix();
	lightMatrixPtr->dirLightView = directionalLight->getViewMatrix();

	//Pointlight
	//For every pointlight send the projection matrix of the pointlight.
	for (size_t i = 0; i < numberOfPointlights; i++)
	{
		//Get projection Matrix of pointlight
		lightMatrixPtr->pointlightProjection[i] = pointlight[i]->getProjectionMatrix();
	}

	//For every element in view array transpone and send to GPU buffer
	for (size_t i = 0; i < numberOfPointlights*6; i++)
	{
		lightMatrixPtr->pointlightView[i] = XMMatrixTranspose(pointlightViewMatrix[i]);
	}

	
	deviceContext->Unmap(lightMatrixBuffer, 0);


	//Set buffers
	deviceContext->PSSetConstantBuffers(0, 1, &dirLightBuffer);
	deviceContext->PSSetConstantBuffers(1, 1, &pointLightBuffer);
	deviceContext->PSSetConstantBuffers(2, 1, &lightMatrixBuffer);


	//Send Heightmap
	deviceContext->PSSetShaderResources(0, 1, &texture);
	//Set the Depth Texture for directional light
	deviceContext->PSSetShaderResources(1, 1, &directionalDepthTex);
	//Send array of pointlight Depthmaps 
	deviceContext->PSSetShaderResources(2, numberOfPointlights*6, pointDepthTex);

	//Set samplers
	deviceContext->PSSetSamplers(0, 1, &sampleState);
	deviceContext->PSSetSamplers(1, 1, &sampleStateShadow);


}


