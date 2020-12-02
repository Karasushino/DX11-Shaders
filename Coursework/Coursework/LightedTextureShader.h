#pragma once

#include "BaseShader.h"
#include "DXF.h"

using namespace std;
using namespace DirectX;

class LightedTextureShader : public BaseShader
{
public:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient[3];
		XMFLOAT4 diffuse[3];
		XMFLOAT4 position[3];
		XMFLOAT4 direction[3];
		XMFLOAT4 attenuation[3];
	};

	LightedTextureShader(ID3D11Device* device, HWND hwnd);
	~LightedTextureShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* texture,
		ID3D11ShaderResourceView* depthMap, Light* light[]);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* lightBuffer;

	ID3D11SamplerState* sampleState;
	ID3D11SamplerState* sampleStateShadow;
};

