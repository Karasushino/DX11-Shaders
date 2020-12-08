// geometry shader.cpp
#include "geometryshader.h"

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

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC grassBufferDesc;
	grassBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	grassBufferDesc.ByteWidth = sizeof(GrassBufferType);
	grassBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	grassBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	grassBufferDesc.MiscFlags = 0;
	grassBufferDesc.StructureByteStride = 0;
	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	renderer->CreateBuffer(&grassBufferDesc, NULL, &grassBuffer);

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
	, ID3D11ShaderResourceView* grassNoise, float amplitude)
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


}
