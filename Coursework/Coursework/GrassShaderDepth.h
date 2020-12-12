//Optimized grass shader only for depth pass with no pixel buffers or unecessary calculations.
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"
using namespace std;
using namespace DirectX;


class GrassShaderDepth : public BaseShader
{

public:

	GrassShaderDepth(ID3D11Device* device, HWND hwnd);
	~GrassShaderDepth();



	struct GrassBufferType
	{
		float time;
		float maxHeight;
		float width;
		float windStrength;

		float frequency;
		float spawnTreshold;
		XMFLOAT2 padding;
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


	struct GrassDensityBufferType
	{
		float density;
		XMFLOAT3 padding;
	};
	void setHullshaderParameters(ID3D11DeviceContext* deviceContext, float grassDensity);

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
		, ID3D11ShaderResourceView* grassNoise, float amplitude);

	void setGeometryShaderParameters(ID3D11DeviceContext* deviceContext, float maxHeight, float width, float windStrength, float frequency, float time, float spawnTreshold);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename);


private:
	D3D11_MAPPED_SUBRESOURCE mappedResource;


	ID3D11Buffer* matrixBuffer;	//Buffer containing view,projection and world matrices.
	ID3D11Buffer* grassBuffer; //Buffer containing the grass settings.
	ID3D11Buffer* heightmapBuffer; //Buffer containing the data settings of the heightmap (amplitude).


	ID3D11Buffer* hullBuffer; //Buffer for the density of the grass.

	ID3D11SamplerState* sampleStateShadow; //Sampler state to sample depth maps.
};
