// depth shader.cpp
#include "DepthShaderHeightmap.h"

DepthShaderHeightmap::DepthShaderHeightmap(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"heightmap_vs.cso", L"heightmap_hs.cso",L"heightmap_ds.cso",L"depth_ps.cso");
}

DepthShaderHeightmap::~DepthShaderHeightmap()
{
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

void DepthShaderHeightmap::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC heightmapBufferDesc;
	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);
	

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	heightmapBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	heightmapBufferDesc.ByteWidth = sizeof(HeightMapBufferType);
	heightmapBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	heightmapBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	heightmapBufferDesc.MiscFlags = 0;
	heightmapBufferDesc.StructureByteStride = 0;


	renderer->CreateBuffer(&heightmapBufferDesc, NULL, &heighMapBuffer);
	

}

void DepthShaderHeightmap::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
}




void DepthShaderHeightmap::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	float InputAmplitude, ID3D11ShaderResourceView* heightmapTexture)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	
	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(worldMatrix);
	XMMATRIX tview = XMMatrixTranspose(viewMatrix);
	XMMATRIX tproj = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;

	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->DSSetConstantBuffers(0, 1, &matrixBuffer);

	// Lock the constant buffer so it can be written to.
	deviceContext->Map(heighMapBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HeightMapBufferType* heightPtr = (HeightMapBufferType*)mappedResource.pData;
	heightPtr->padding = XMFLOAT3(0.0f, 0.0f, 0.0f);
	heightPtr->amplitude = InputAmplitude;
	deviceContext->Unmap(heighMapBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &heighMapBuffer);
	deviceContext->DSSetShaderResources(0, 1, &heightmapTexture);

}
