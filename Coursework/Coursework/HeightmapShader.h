// Light shader.h
// Basic single light shader setup
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"

using namespace std;
using namespace DirectX;


class HeightmapShader : public BaseShader
{

public:

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		
	};

	//Define number of Pointlights
	static const int numberOfPointlights = 1;
	struct LightMatrixBufferType
	{
		//Directional light matrix
		XMMATRIX dirLightView;
		XMMATRIX dirLightProjection;
		//Pointlight matrix
		XMMATRIX pointlightProjection[numberOfPointlights];
		XMMATRIX pointlightView[numberOfPointlights*6];
	};

	struct HullBufferType {
		XMFLOAT4 TessellationFactor;
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

	struct DirectionalLightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 direction;
	};

	struct PointlightBufferType
	{
		XMFLOAT4 diffuse[numberOfPointlights];
		XMFLOAT4 position[numberOfPointlights];
	};


	HeightmapShader(ID3D11Device* device, HWND hwnd);
	~HeightmapShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
		XMFLOAT4 TesselationFactor, ID3D11ShaderResourceView* texture, XMFLOAT3 CameraPosInput, float amplitude, ID3D11ShaderResourceView* heightmapTexture,
		Light* directionalLight,Light* pointlight[], ID3D11ShaderResourceView* directionalDepthTex, ID3D11ShaderResourceView* pointDepthTex[],XMMATRIX pointlightViewMatrix[]);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* lightMatrixBuffer;

	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* cameraBuffer;
	ID3D11Buffer* heighMapBuffer;
	ID3D11Buffer* dirLightBuffer;
	ID3D11Buffer* pointLightBuffer;

	ID3D11SamplerState* sampleStateShadow;
};
