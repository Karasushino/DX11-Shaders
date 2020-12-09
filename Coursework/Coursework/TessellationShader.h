// Light shader.h
// Basic single light shader setup
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"

using namespace std;
using namespace DirectX;


class TessellationShader : public BaseShader
{

public:

	struct HullBufferType {
		float tessellationFactor;
		float dynamicTessellationFactor;
		int dynmaicTesellationToggle;
		float distanceScalar;
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

	struct WaterBufferType
	{
		float heightmapAmplitude;
		float waterPlaneHeight;
		float offsett;
		float depthScalar;
	};

	struct WaterColorBufferType
	{
		XMFLOAT4 deepColor;
		XMFLOAT4 shallowColor;
	};



	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	void setHullShaderParameters(ID3D11DeviceContext* deviceContext, float tessellationFactor, float dynamicTessellationFactor,
		bool dynmaicTesellationToggle, float distanceScalar);

	void setPixelShaderParameters(ID3D11DeviceContext* deviceContext, float waterOffset, float depthScalar, float Sealevel, float amplitude, float deepColor[4],
		float shallowColor[4], ID3D11ShaderResourceView* heightTexture);

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
		XMFLOAT4 EdgeTesellation, XMFLOAT2 InsideTesellation, XMFLOAT3 CameraPosInput, XMFLOAT4 InputWaveSettings[],
		float direction[], float time);

	

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;



	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* SeaBuffer;

	ID3D11Buffer* WaterBuffer;
	ID3D11Buffer* WaterColorBuffer;
};
