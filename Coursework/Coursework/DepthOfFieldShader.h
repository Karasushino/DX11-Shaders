#pragma once
// Depth of field shader that takes the blurred scene and then blends it with the unblurred.

// Loads  Depth of field blur shaders (vs and ps)
// Passes a depth map to do the calculations of whether it should blur or not.

#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class DepthOfFieldShader : public BaseShader
{
private:

	

public:

	struct DOFBufferType
	{
		float distance;
		float range;
		float nearPlane;
		float farPlane;
	};

	DepthOfFieldShader(ID3D11Device* device, HWND hwnd);
	~DepthOfFieldShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection, ID3D11ShaderResourceView* SceneTexture,
		ID3D11ShaderResourceView* BlurredScene, ID3D11ShaderResourceView* depthMap, XMFLOAT4 DepthOfFieldSettings);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer* matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* dofBuffer;
};