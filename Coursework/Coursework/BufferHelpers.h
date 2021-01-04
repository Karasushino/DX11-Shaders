#pragma once
//Header file with Static functions desgined to make me type less.
#include "DXF.h"

using namespace DirectX;

class BufferHelpers
{
public:

	
	//Creates a Default Buffer Description @param ByteWidth of the Buffer, use sizeof().
	static D3D11_BUFFER_DESC CreateBufferDescription(UINT ByteWidth)
	{
		D3D11_BUFFER_DESC bufferDesc;

		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		// Note: ByteWidth ALWAYS must be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER else CreateBuffer() will fail.
		bufferDesc.ByteWidth = ByteWidth;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		return bufferDesc;
	}

	//Creates a Default Sampler Description
	static D3D11_SAMPLER_DESC CreateSamplerDescription()
	{
		D3D11_SAMPLER_DESC samplerDesc;

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return samplerDesc;
	}

	//Creates a Shadow Sampler Description
	static D3D11_SAMPLER_DESC CreateShadowSamplerDescription()
	{
		D3D11_SAMPLER_DESC samplerDesc;

		// Sampler for shadow map sampling.
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 1.0f;
		samplerDesc.BorderColor[2] = 1.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		return samplerDesc;
	}
	

};
