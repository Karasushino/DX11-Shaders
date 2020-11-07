// Light shader.h
// Basic single light shader setup
#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;


class TessellationShader : public BaseShader
{

public:

	struct HullBufferType {
		XMFLOAT4 Edges;
		XMFLOAT2 Inside;
		XMFLOAT2 padding;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

	struct HeightMapBufferType
	{
		float amplitude;
		XMFLOAT3 padding;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient[3];
		XMFLOAT4 diffuse[3];
		XMFLOAT4 position[3];
		XMFLOAT4 direction[3];
		XMFLOAT4 attenuation[3];
	};



	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		XMFLOAT4 EdgeTesselation, XMFLOAT2 InsideTesselation,ID3D11ShaderResourceView* texture, XMFLOAT3 CameraPosInput, float amplitude, ID3D11ShaderResourceView* heightmapTexture,
		Light* light[]);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* heighMapBuffer;
	ID3D11Buffer* lightBuffer;

};
