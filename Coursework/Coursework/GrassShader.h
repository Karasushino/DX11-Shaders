//Geometry Grass Shader.
#pragma once

#include "DXF.h"
#include "BufferHelpers.h"
using namespace std;
using namespace DirectX;


class GrassShader : public BaseShader
{

public:

	GrassShader(ID3D11Device* device, HWND hwnd);
	~GrassShader();

	

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

	struct GrassColorBufferType
	{
		XMFLOAT4 bottomColor;
		XMFLOAT4 topColor;
	};

	struct GrassDensityBufferType
	{
		float density;
		XMFLOAT3 padding;
	};
	void setHullshaderParameters(ID3D11DeviceContext* deviceContext, float grassDensity);

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* height, ID3D11ShaderResourceView* noise
		, ID3D11ShaderResourceView* grassNoise, float amplitude, Light* directionalLight, ID3D11ShaderResourceView* directionalDepthTex);

	void setPixelShaderParameters(ID3D11DeviceContext* deviceContext, float bottomColor[4], float topColor[4]);

	void setGeometryShaderParameters(ID3D11DeviceContext* deviceContext, float maxHeight, float width, float windStrength, float frequency, float time, float spawnTreshold);

private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* gsFilename, const wchar_t* psFilename);


private:
	D3D11_MAPPED_SUBRESOURCE mappedResource;


	ID3D11Buffer* matrixBuffer;	//Buffer containing view,projection and world matrices.
	ID3D11Buffer* grassBuffer;	//Buffer containing the grass settings.
	ID3D11Buffer* heightmapBuffer; //Buffer containing the data settings of the heightmap (amplitude).

	//Lighting buffer and samplers
	ID3D11Buffer* lightMatrixBuffer; //Buffer containing all the matrix data for lights.
	ID3D11Buffer* dirLightBuffer; //Directional light buffer data.
	ID3D11Buffer* pointLightBuffer; //Pointlight buffer data.
	
	ID3D11Buffer* hullBuffer; //Buffer for the density of the grass.

	ID3D11Buffer* grassColorbuffer; //Buffer that contains the 2 colors of the grass.

	ID3D11SamplerState* sampleStateShadow; //Sampler state to sample depth maps.
};
