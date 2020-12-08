// Light shader.h
// Geometry shader example.
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"
using namespace std;
using namespace DirectX;


class GeometryShaderDepth : public BaseShader
{

public:

	GeometryShaderDepth(ID3D11Device* device, HWND hwnd);
	~GeometryShaderDepth();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,ID3D11ShaderResourceView* texture,float time, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
		, ID3D11ShaderResourceView* grassNoise, float amplitude);

	struct GrassBufferType
	{
		float time;
		XMFLOAT3 padding;
	};

	struct HeightmapBufferType
	{
		float amplitude;
		XMFLOAT3 padding;
	};

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* grassBuffer;
	ID3D11Buffer* heightmapBuffer;


};
