//Heightmap shader.

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
	static const int numberOfPointlights = 2;
	struct LightMatrixBufferType
	{
		//Directional light matrix
		XMMATRIX dirLightView;
		XMMATRIX dirLightProjection;
		//Pointlight matrix
		XMMATRIX pointlightProjection[numberOfPointlights];
		XMMATRIX pointlightView[numberOfPointlights*6];
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
		XMFLOAT4 attenuation[numberOfPointlights];

	};

	struct TilingBufferType
	{
		float tiling;
		XMFLOAT3 padding;
	};


	struct TessellationBufferType {
		float tessellationFactor;
		float dynamicTessellationFactor;
		int dynmaicTesellationToggle;
		float distanceScalar;
	};



	HeightmapShader(ID3D11Device* device, HWND hwnd);
	~HeightmapShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection,
  ID3D11ShaderResourceView* texture, XMFLOAT3 CameraPosInput, float amplitude, ID3D11ShaderResourceView* heightmapTexture,
		Light* directionalLight,Light* pointlight[], ID3D11ShaderResourceView* directionalDepthTex, ID3D11ShaderResourceView* pointDepthTex[],XMMATRIX pointlightViewMatrix[],
		float tiling);

	void setHullShaderParameters(ID3D11DeviceContext* deviceContext, float tessellationFactor, float dynamicTessellationFactor, bool dynmaicTesellationToggle, float distanceScalar);


private:
	void initShader(const wchar_t* vsFilename, const wchar_t* psFilename);
	void initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename);

private:

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	ID3D11Buffer* matrixBuffer; //Buffer containing view,projection and world matrices.

	ID3D11Buffer* cameraBuffer; //Buffer containing position of camera.

	ID3D11Buffer* heighMapBuffer;  //Buffer with all the Heightmap Settings.

	ID3D11Buffer* tessellationBuffer; //Buffer containing data for tessellation.

	ID3D11Buffer* tilingBuffer; //Buffer with a variable to change texture tiling.

	//Light Buffers
	ID3D11Buffer* dirLightBuffer; //Directional light buffer data.
	ID3D11Buffer* pointLightBuffer; //Pointlight buffer data.
	ID3D11Buffer* lightMatrixBuffer; //Buffer containing all the matrix data for lights.
	ID3D11SamplerState* sampleStateShadow; //Sampler state to sample depth maps.
};
