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

	struct SeaBufferType
	{
		XMFLOAT4 WaveSettings;
		XMFLOAT3 WaveDirection;
		float WaveSmoothness;
	};

	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		XMFLOAT4 EdgeTesselation, XMFLOAT2 InsideTesselation, XMFLOAT3 CameraPosInput, XMFLOAT4 inputWaveSettings, ID3D11ShaderResourceView* heightmapTexture,
		XMFLOAT3 InputWaveDirection, float WaveSmoothness);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* SeaBuffer;
};
