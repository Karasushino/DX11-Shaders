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
		XMFLOAT4 WaveSettings[3];
		XMFLOAT4 WaveDirectionTimePadding[3];

	};

	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
		XMFLOAT4 EdgeTesellation, XMFLOAT2 InsideTesellation, XMFLOAT3 CameraPosInput, XMFLOAT4 InputWaveSettings[], ID3D11ShaderResourceView* texture,
		float direction[], float time);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* SeaBuffer;
};
