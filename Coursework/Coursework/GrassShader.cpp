// geometry shader.cpp
#include "GrassShader.h"

GrassShader::GrassShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"grass_vs.cso",L"grass_hs.cso", L"grass_ds.cso" ,L"grass_gs.cso", L"grass_ps.cso");
}

GrassShader::~GrassShader()
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

	// Release the matrix constant buffer.
	if (grassBuffer)
	{
		grassBuffer->Release();
		grassBuffer = 0;
	}

	// Release the heightmap constant buffer.
	if (heightmapBuffer)
	{
		heightmapBuffer->Release();
		heightmapBuffer = 0;
	}

	// Release the hull constant buffer.
	if (hullBuffer)
	{
		hullBuffer->Release();
		hullBuffer = 0;
	}

	// Release the sampler for shadows.
	if (sampleStateShadow)
	{
		sampleStateShadow->Release();
		sampleStateShadow = 0;
	}

	// Release the buffer of the light matrices.
	if (lightMatrixBuffer)
	{
		lightMatrixBuffer->Release();
		lightMatrixBuffer = 0;
	}

	// Release the buffer for directional light.
	if (dirLightBuffer)
	{
		dirLightBuffer->Release();
		dirLightBuffer = 0;
	}


	// Release the grass buffer.
	if (grassColorbuffer)
	{
		grassColorbuffer->Release();
		grassColorbuffer = 0;
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


void GrassShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
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

	//Setup the description of Matrix Buffer.
	D3D11_BUFFER_DESC matrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(MatrixBufferType));
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	//Setup the description of Grass Buffer.
	D3D11_BUFFER_DESC grassBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassBufferType));
	renderer->CreateBuffer(&grassBufferDesc, NULL, &grassBuffer);

	// Setup the description of the dynamic matrix constant buffer of the lights that is in the pixel shader.
	D3D11_BUFFER_DESC lightMatrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(LightMatrixBufferType));
	renderer->CreateBuffer(&lightMatrixBufferDesc, NULL, &lightMatrixBuffer);

	// Setup light settings buffer Pixel shader.
	D3D11_BUFFER_DESC lightBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(DirectionalLightBufferType));
	renderer->CreateBuffer(&lightBufferDesc, NULL, &dirLightBuffer);

	//Buffer description settings for the heightmap.
	D3D11_BUFFER_DESC heightmapBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HeightmapBufferType));
	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heightmapBuffer);

	//Setup Buffer description of the Buffer to set the color settings of the grass.
	D3D11_BUFFER_DESC grassColorBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassColorBufferType));
	renderer->CreateBuffer(&grassColorBufferDesc, NULL, &grassColorbuffer);

	//Setup Hull buffer to control density of grass.
	D3D11_BUFFER_DESC hullBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassDensityBufferType));
	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);

}

void GrassShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
	loadGeometryShader(gsFilename);
}


void GrassShader::setHullshaderParameters(ID3D11DeviceContext* deviceContext, float grassDensity)
{

	GrassDensityBufferType* densityPtr;

	deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set density buffer data.
	densityPtr = (GrassDensityBufferType*)mappedResource.pData;
	densityPtr->density = grassDensity;
	densityPtr->padding = XMFLOAT3(0, 0, 0);

	deviceContext->Unmap(hullBuffer, 0);

	deviceContext->HSSetConstantBuffers(1, 1, &hullBuffer);
}

void GrassShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
	,ID3D11ShaderResourceView* grassNoise, float amplitude, Light* directionalLight, ID3D11ShaderResourceView* directionalDepthTex)
{
	MatrixBufferType* dataPtr;

	//Transpose the matrices to prepare them for the shader.
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

	//Pixel Shader Parameters
 
	// Send light data to pixel shader
	DirectionalLightBufferType* dirLightPtr;
	deviceContext->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	dirLightPtr = (DirectionalLightBufferType*)mappedResource.pData;
	dirLightPtr->ambient = directionalLight->getAmbientColour();
	dirLightPtr->diffuse = directionalLight->getDiffuseColour();
	// Set buffer pointer with directionalLight position -->  Note: I hate that I can't do getPosition().xyz, makes line too long.
	dirLightPtr->direction = XMFLOAT4(directionalLight->getDirection().x, directionalLight->getDirection().y, directionalLight->getDirection().z, 1.f);

	deviceContext->Unmap(dirLightBuffer, 0);

	
	//Set light matrix buffer
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

	//use default sampler and set distortion texture to bend grass
	deviceContext->GSSetShaderResources(0, 1, &texture);
	deviceContext->GSSetShaderResources(1, 1, &noise);
	deviceContext->GSSetShaderResources(2, 1, &grassNoise);

}

void GrassShader::setPixelShaderParameters(ID3D11DeviceContext* deviceContext, float bottomColor[4], float topColor[4])
{
	//Pixel Shader Parameters

	//Send data about the color of the grass
	GrassColorBufferType* grassPtr;
	deviceContext->Map(grassColorbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	grassPtr = (GrassColorBufferType*)mappedResource.pData;
	grassPtr->bottomColor = XMFLOAT4(bottomColor[0], bottomColor[1], bottomColor[2], bottomColor[3]);
	grassPtr->topColor = XMFLOAT4(topColor[0], topColor[1], topColor[2], topColor[3]);

	deviceContext->Unmap(grassColorbuffer, 0);

	deviceContext->PSSetConstantBuffers(2, 1, &grassColorbuffer);


}

void GrassShader::setGeometryShaderParameters(ID3D11DeviceContext* deviceContext, float maxHeight, float width, float windStrength, float frequency,float time, float spawnTreshold)
{
	//Set grass buffer settings
	GrassBufferType* grassPtr;
	deviceContext->Map(grassBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	grassPtr = (GrassBufferType*)mappedResource.pData;

	grassPtr->frequency = frequency;
	grassPtr->maxHeight = maxHeight;
	grassPtr->width = width;
	grassPtr->windStrength = windStrength;

	grassPtr->time = time;// worldMatrix;
	grassPtr->spawnTreshold = spawnTreshold;
	grassPtr->padding = XMFLOAT2(0, 0);
	deviceContext->Unmap(grassBuffer, 0);
	deviceContext->GSSetConstantBuffers(1, 1, &grassBuffer);
	
	deviceContext->GSSetSamplers(0, 1, &sampleState);

}
