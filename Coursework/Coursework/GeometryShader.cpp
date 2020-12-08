// geometry shader.cpp
#include "GeometryShader.h"

GeometryShader::GeometryShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"triangle_vs.cso",L"triangle_hs.cso", L"triangle_ds.cso" ,L"triangle_gs.cso", L"triangle_ps.cso");
}

GeometryShader::~GeometryShader()
{
	// Release the sampler state.
	if (sampleState)
	{
		sampleState->Release();
		sampleState = 0;
	}

	// Release the matrix constant buffer.
	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}

void GeometryShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
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

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC grassBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassBufferType));
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&grassBufferDesc, NULL, &grassBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the pixel shader.
		D3D11_BUFFER_DESC lightMatrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(LightMatrixBufferType));
	renderer->CreateBuffer(&lightMatrixBufferDesc, NULL, &lightMatrixBuffer);

	// Setup light buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC lightBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(DirectionalLightBufferType));

	renderer->CreateBuffer(&lightBufferDesc, NULL, &dirLightBuffer);


	D3D11_BUFFER_DESC heightmapBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HeightmapBufferType));
	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heightmapBuffer);


}

void GeometryShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
	loadGeometryShader(gsFilename);
}


void GeometryShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, float time, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
	,ID3D11ShaderResourceView* grassNoise, float amplitude, Light* directionalLight, ID3D11ShaderResourceView* directionalDepthTex)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	
	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(worldMatrix);
	XMMATRIX tview = XMMatrixTranspose(viewMatrix);
	XMMATRIX tproj = XMMatrixTranspose(projectionMatrix);

	deviceContext->HSSetShaderResources(0, 1, &grassNoise);

	deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->GSSetConstantBuffers(0, 1, &matrixBuffer);
	deviceContext->DSSetConstantBuffers(0, 1, &matrixBuffer);
	deviceContext->DSSetShaderResources(0, 1, &height);

	//Set buffer for variable amplitude of heightmap
	HeightmapBufferType* heightPtr;
	deviceContext->Map(heightmapBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	heightPtr = (HeightmapBufferType*)mappedResource.pData;
	heightPtr->amplitude = amplitude;
	heightPtr->padding = XMFLOAT3(0, 0, 0);
	deviceContext->Unmap(heightmapBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &heightmapBuffer);

	//Set grass buffer
	GrassBufferType* grassPtr;
	deviceContext->Map(grassBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	grassPtr = (GrassBufferType*)mappedResource.pData;
	grassPtr->time = time;// worldMatrix;
	grassPtr->padding = XMFLOAT3(0, 0, 0);
	deviceContext->Unmap(grassBuffer, 0);
	deviceContext->GSSetConstantBuffers(1, 1, &grassBuffer);

	//use default sampler and set distortion texture to bend grass
	deviceContext->GSSetShaderResources(0,1,&texture);
	deviceContext->GSSetShaderResources(1, 1, &noise);
	deviceContext->GSSetShaderResources(2, 1, &grassNoise);
	deviceContext->GSSetSamplers(0, 1, &sampleState);

	//ps
 
	// Send light data to pixel shader
	DirectionalLightBufferType* dirLightPtr;
	deviceContext->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	dirLightPtr = (DirectionalLightBufferType*)mappedResource.pData;
	dirLightPtr->ambient = directionalLight->getAmbientColour();
	dirLightPtr->diffuse = directionalLight->getDiffuseColour();
	// Set buffer pointer with pointlight position -->  Note: I hate that I can't do getPosition().xyz, makes line too long.
	dirLightPtr->direction = XMFLOAT4(directionalLight->getDirection().x, directionalLight->getDirection().y, directionalLight->getDirection().z, 1.f);

	deviceContext->Unmap(dirLightBuffer, 0);

	
	//Set pointlight light buffer
	LightMatrixBufferType* lightMatrixPtr;
	deviceContext->Map(lightMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightMatrixPtr = (LightMatrixBufferType*)mappedResource.pData;

	//Directional Light
	//Get orthomatrix
	lightMatrixPtr->dirLightProjection = XMMatrixTranspose(directionalLight->getOrthoMatrix());
	//Need to update view matrix
	directionalLight->generateViewMatrix();
	lightMatrixPtr->dirLightView = XMMatrixTranspose(directionalLight->getViewMatrix());


	deviceContext->Unmap(lightMatrixBuffer, 0);


	//Set buffers
	deviceContext->PSSetConstantBuffers(0, 1, &dirLightBuffer);
	deviceContext->PSSetConstantBuffers(1, 1, &lightMatrixBuffer);

}
