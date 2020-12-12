// geometry shader.cpp
#include "GrassShaderDepth.h"

GrassShaderDepth::GrassShaderDepth(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"grass_vs.cso", L"grass_hs.cso", L"grass_ds.cso", L"grass_gs.cso", L"depth_ps.cso");
}

GrassShaderDepth::~GrassShaderDepth()
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

	// Release the layout.
	if (layout)
	{
		layout->Release();
		layout = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}


void GrassShaderDepth::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);
	//Sampler for normal textures
	D3D11_SAMPLER_DESC samplerDesc = BufferHelpers::CreateSamplerDescription();
	renderer->CreateSamplerState(&samplerDesc, &sampleState);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(MatrixBufferType));
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC grassBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassBufferType));
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&grassBufferDesc, NULL, &grassBuffer);

	D3D11_BUFFER_DESC heightmapBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HeightmapBufferType));
	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heightmapBuffer);


	D3D11_BUFFER_DESC hullBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(GrassDensityBufferType));
	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);

}

void GrassShaderDepth::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
	loadGeometryShader(gsFilename);
}


void GrassShaderDepth::setHullshaderParameters(ID3D11DeviceContext* deviceContext, float grassDensity)
{
	//Pixel Shader Parameters

	// Send light data to pixel shader
	GrassDensityBufferType* densityPtr;

	deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	densityPtr = (GrassDensityBufferType*)mappedResource.pData;
	densityPtr->density = grassDensity;
	densityPtr->padding = XMFLOAT3(0, 0, 0);

	deviceContext->Unmap(hullBuffer, 0);

	deviceContext->HSSetConstantBuffers(1, 1, &hullBuffer);
}

void GrassShaderDepth::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
	, ID3D11ShaderResourceView* grassNoise, float amplitude)
{
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

	
	//use default sampler and set distortion texture to bend grass
	deviceContext->GSSetShaderResources(0, 1, &texture);
	deviceContext->GSSetShaderResources(1, 1, &noise);
	deviceContext->GSSetShaderResources(2, 1, &grassNoise);

}


void GrassShaderDepth::setGeometryShaderParameters(ID3D11DeviceContext* deviceContext, float maxHeight, float width, float windStrength, float frequency, float time, float spawnTreshold)
{
	//Set grass buffer
	GrassBufferType* grassPtr;
	deviceContext->Map(grassBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	grassPtr = (GrassBufferType*)mappedResource.pData;

	grassPtr->frequency = frequency;
	grassPtr->maxHeight = maxHeight;
	grassPtr->width = width;
	grassPtr->windStrength = windStrength;

	grassPtr->time = time;
	grassPtr->spawnTreshold = spawnTreshold;
	grassPtr->padding = XMFLOAT2(0, 0);
	deviceContext->Unmap(grassBuffer, 0);
	deviceContext->GSSetConstantBuffers(1, 1, &grassBuffer);

	deviceContext->GSSetSamplers(0, 1, &sampleState);

}