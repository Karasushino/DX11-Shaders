// Colour shader.h
// Simple shader example.
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class DepthShaderHeightmap : public BaseShader
{

public:

	struct HeightMapBufferType
	{
		float amplitude;
		XMFLOAT3 padding;
	};
	DepthShaderHeightmap(ID3D11Device* device, HWND hwnd);
	~DepthShaderHeightmap();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection,
		float InputAmplitude, ID3D11ShaderResourceView* heightmapTexture);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer; //Buffer containing view,projection and world matrices.
	ID3D11Buffer* heighMapBuffer; //Buffer with all the Heightmap Settings.
};
