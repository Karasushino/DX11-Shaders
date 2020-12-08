// Light shader.h
// Geometry shader example.
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"
using namespace std;
using namespace DirectX;


class GeometryShader : public BaseShader
{

public:

	GeometryShader(ID3D11Device* device, HWND hwnd);
	~GeometryShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,ID3D11ShaderResourceView* texture,float time, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
		, ID3D11ShaderResourceView* grassNoise, float amplitude, Light* directionalLight, ID3D11ShaderResourceView* directionalDepthTex);

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

	//Define number of Pointlights
	static const int numberOfPointlights = 1;
	struct LightMatrixBufferType
	{
		//Directional light matrix
		XMMATRIX dirLightView;
		XMMATRIX dirLightProjection;
	};

	struct HullBufferType {
		XMFLOAT4 TessellationFactor;
	};


	struct DirectionalLightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 direction;
	};


private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* grassBuffer;
	ID3D11Buffer* heightmapBuffer;


	ID3D11Buffer* lightMatrixBuffer;
	ID3D11Buffer* hullBuffer;
	ID3D11Buffer* dirLightBuffer;

	ID3D11SamplerState* sampleStateShadow;
};
