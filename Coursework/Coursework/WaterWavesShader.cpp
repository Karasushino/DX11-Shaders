//Water simulation shader.
#include "WaterWavesShader.h"


WaterWavesShader::WaterWavesShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	initShader(L"water_vs.cso", L"water_hs.cso", L"water_ds.cso", L"water_ps.cso");
}


WaterWavesShader::~WaterWavesShader()
{
	if (sampleState)
	{
		sampleState->Release();
		sampleState = 0;
	}

	if (matrixBuffer)
	{
		matrixBuffer->Release();
		matrixBuffer = 0;
	}

	if (hullBuffer)
	{
		hullBuffer->Release();
		hullBuffer = 0;
	}

	if (cameraBuffer)
	{
		cameraBuffer->Release();
		cameraBuffer = 0;
	}

	if (SeaBuffer)
	{
		SeaBuffer->Release();
		SeaBuffer = 0;
	}

	if (WaterBuffer)
	{
		WaterBuffer->Release();
		WaterBuffer = 0;
	}

	if (WaterColorBuffer)
	{
		WaterColorBuffer->Release();
		WaterColorBuffer = 0;
	}

	if (lightMatrixBuffer)
	{
		lightMatrixBuffer->Release();
		lightMatrixBuffer = 0;
	}

	if (dirLightBuffer)
	{
		dirLightBuffer->Release();
		dirLightBuffer = 0;
	}

	if (pointLightBuffer)
	{
		pointLightBuffer->Release();
		pointLightBuffer = 0;
	}

	if (sampleStateShadow)
	{
		sampleStateShadow->Release();
		sampleStateShadow = 0;
	}

	if (layout)
	{
		layout->Release();
		layout = 0;
	}
	
	//Release base shader components
	BaseShader::~BaseShader();
}

void WaterWavesShader::initShader(const wchar_t* vsFilename, const wchar_t* psFilename)
{
	

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(MatrixBufferType));
	renderer->CreateBuffer(&matrixBufferDesc, NULL, &matrixBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC hullBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(HullBufferType));
	renderer->CreateBuffer(&hullBufferDesc, NULL, &hullBuffer);



	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC cameraBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(CameraBufferType));
	renderer->CreateBuffer(&cameraBufferDesc, NULL, &cameraBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC SeaBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(SeaBufferType));
	renderer->CreateBuffer(&SeaBufferDesc, NULL, &SeaBuffer);


	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC waterBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(WaterBufferType));
	renderer->CreateBuffer(&waterBufferDesc, NULL, &WaterBuffer);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC waterColorBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(WaterColorBufferType));
	renderer->CreateBuffer(&waterColorBufferDesc, NULL, &WaterColorBuffer);


	//Lighting buffers
	//Setup directioanl light buffer
	//Setup the description of the light dynamic constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC lightBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(DirectionalLightBufferType));

	renderer->CreateBuffer(&lightBufferDesc, NULL, &dirLightBuffer);

	//Setup pointlight buffer
	//Setup the description of the light dynamic constant buffer that is in the pixel shader.
	D3D11_BUFFER_DESC pointLightDesc = BufferHelpers::CreateBufferDescription(sizeof(PointlightBufferType));
	renderer->CreateBuffer(&pointLightDesc, NULL, &pointLightBuffer);

	// Setup the description of the dynamic matrix constant buffer of the light that is in the pixel shader.
	D3D11_BUFFER_DESC lightMatrixBufferDesc = BufferHelpers::CreateBufferDescription(sizeof(LightMatrixBufferType));
	renderer->CreateBuffer(&lightMatrixBufferDesc, NULL, &lightMatrixBuffer);

	//Sampler for DepthMaps
	D3D11_SAMPLER_DESC shadowSamplerDesc = BufferHelpers::CreateShadowSamplerDescription();
	renderer->CreateSamplerState(&shadowSamplerDesc, &sampleStateShadow);

}

void WaterWavesShader::initShader(const wchar_t* vsFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* psFilename)
{
	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	initShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);
}

void WaterWavesShader::setHullShaderParameters(ID3D11DeviceContext* deviceContext, float tessellationFactor, float dynamicTessellationFactor, bool dynmaicTesellationToggle, float distanceScalar)
{

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(hullBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	HullBufferType* HullPtr = (HullBufferType*)mappedResource.pData;
	HullPtr->distanceScalar = distanceScalar;
	HullPtr->dynamicTessellationFactor = dynamicTessellationFactor;
	HullPtr->dynmaicTesellationToggle = dynmaicTesellationToggle;
	HullPtr->tessellationFactor = tessellationFactor;
	deviceContext->Unmap(hullBuffer, 0);
	deviceContext->HSSetConstantBuffers(0, 1, &hullBuffer);
}

void WaterWavesShader::setPixelShaderParameters(ID3D11DeviceContext* deviceContext, float waterOffset, float depthScalar, float Sealevel, float amplitude, float deepColor[4],
	float shallowColor[4], ID3D11ShaderResourceView* heightTexture)
{
	result = deviceContext->Map(WaterBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	WaterBufferType* waterPtr = (WaterBufferType*)mappedResource.pData;

	waterPtr->heightmapAmplitude = amplitude;
	waterPtr->waterPlaneHeight = Sealevel;
	waterPtr->offsett = waterOffset;
	waterPtr->depthScalar = depthScalar;

	deviceContext->Unmap(WaterBuffer, 0);


	result = deviceContext->Map(WaterColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	WaterColorBufferType* waterColorPtr = (WaterColorBufferType*)mappedResource.pData;

	waterColorPtr->deepColor = XMFLOAT4(deepColor[0], deepColor[1], deepColor[2], deepColor[3]);
	waterColorPtr->shallowColor = XMFLOAT4(shallowColor[0], shallowColor[1], shallowColor[2], shallowColor[3]);
	
	deviceContext->Unmap(WaterColorBuffer, 0);


	deviceContext->PSSetConstantBuffers(1, 1, &WaterBuffer);
	deviceContext->PSSetConstantBuffers(2, 1, &WaterColorBuffer);

	deviceContext->PSSetShaderResources(1, 1, &heightTexture);
}

void WaterWavesShader::setLightingShaderParameters(ID3D11DeviceContext* deviceContext, Light* directionalLight, Light* pointlight[], ID3D11ShaderResourceView* directionalDepthTex, ID3D11ShaderResourceView* pointDepthTex[], XMMATRIX pointlightViewMatrix[]
	,bool lightToggle)
{

	// Map buffer of the directiona light
	DirectionalLightBufferType* dirLightPtr;
	deviceContext->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	//Set directional light buffer
	dirLightPtr = (DirectionalLightBufferType*)mappedResource.pData;
	dirLightPtr->ambient = directionalLight->getAmbientColour();
	dirLightPtr->diffuse = directionalLight->getDiffuseColour();

	// Set buffer pointer with pointlight position -->  Note: I hate that I can't do getPosition().xyz, makes line too long.
	dirLightPtr->direction = XMFLOAT4(directionalLight->getDirection().x, directionalLight->getDirection().y, directionalLight->getDirection().z, (float)lightToggle);
	dirLightPtr->specularColor = directionalLight->getSpecularColour();
	dirLightPtr->specularPower = directionalLight->getSpecularPower();
	dirLightPtr->padding = XMFLOAT3(0, 0, 0);
	deviceContext->Unmap(dirLightBuffer, 0);


	//Map pointlight buffer
	PointlightBufferType* pointlightPtr;
	deviceContext->Map(pointLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	pointlightPtr = (PointlightBufferType*)mappedResource.pData;

	//Set buffer data
	for (size_t i = 0; i < numberOfPointlights; i++)
	{
		//Set diffuse color.
		pointlightPtr->diffuse[i] = pointlight[i]->getDiffuseColour();
		// Set buffer pointer with pointlight position -->  Note: I hate that I can't do getPosition().xyz, makes line too long.
		pointlightPtr->position[i] = XMFLOAT4(pointlight[i]->getPosition().x, pointlight[i]->getPosition().y, pointlight[i]->getPosition().z, 0.f);
		pointlightPtr->attenuation[i] = XMFLOAT4(pointlight[i]->getAttenuationFactors().x, pointlight[i]->getAttenuationFactors().y, pointlight[i]->getAttenuationFactors().z, 0.f);

	}

	deviceContext->Unmap(pointLightBuffer, 0);

	//Set Light Matrices buffer
	LightMatrixBufferType* lightMatrixPtr;
	deviceContext->Map(lightMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightMatrixPtr = (LightMatrixBufferType*)mappedResource.pData;

	//Directional Light
	//Get orthomatrix
	lightMatrixPtr->dirLightProjection = XMMatrixTranspose(directionalLight->getOrthoMatrix());
	//Need to update view matrix
	directionalLight->generateViewMatrix();
	lightMatrixPtr->dirLightView = XMMatrixTranspose(directionalLight->getViewMatrix());

	//Pointlight
	//For every pointlight send the projection matrix of the pointlight.
	for (size_t i = 0; i < numberOfPointlights; i++)
	{
		//Get projection Matrix of pointlight
		lightMatrixPtr->pointlightProjection[i] = XMMatrixTranspose(pointlight[i]->getProjectionMatrix());
	}

	//For every element in view array transpone and send to GPU buffer
	for (size_t i = 0; i < numberOfPointlights * 6; i++)
	{
		lightMatrixPtr->pointlightView[i] = XMMatrixTranspose(pointlightViewMatrix[i]);
	}


	deviceContext->Unmap(lightMatrixBuffer, 0);

	//Set buffers
	deviceContext->PSSetConstantBuffers(3, 1, &dirLightBuffer);
	deviceContext->PSSetConstantBuffers(4, 1, &pointLightBuffer);
	deviceContext->PSSetConstantBuffers(5, 1, &lightMatrixBuffer);

	//Set the Depth Textures for directional light
	deviceContext->PSSetShaderResources(2, 1, &directionalDepthTex);
	//Send array of pointlight Depthmaps 
	deviceContext->PSSetShaderResources(3, numberOfPointlights * 6, pointDepthTex);

	//Set Shadow Sampler
	deviceContext->PSSetSamplers(1, 1, &sampleStateShadow);

}



void WaterWavesShader::setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX& worldMatrix, const XMMATRIX& viewMatrix, const XMMATRIX& projectionMatrix,
	 XMFLOAT3 CameraPosInput, XMFLOAT4 InputWaveSettings[],float InputWaveDirection[], float time)
{
	

	// Transpose the matrices to prepare them for the shader.
	XMMATRIX tworld = XMMatrixTranspose(worldMatrix);
	XMMATRIX tview = XMMatrixTranspose(viewMatrix);
	XMMATRIX tproj = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	deviceContext->Unmap(matrixBuffer, 0);
	deviceContext->DSSetConstantBuffers(0, 1, &matrixBuffer);


	
	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CameraBufferType* CamPtr = (CameraBufferType*)mappedResource.pData;
	CamPtr->cameraPosition = CameraPosInput;
	CamPtr->padding = 1.0f;
	deviceContext->Unmap(cameraBuffer, 0);
	deviceContext->HSSetConstantBuffers(1, 1, &cameraBuffer);


	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(SeaBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	SeaBufferType* heightPtr = (SeaBufferType*)mappedResource.pData;

	for (int i = 0; i < 3; i++)
	{
		heightPtr->WaveSettings[i] = InputWaveSettings[i];
		heightPtr->WaveDirectionTimePadding[i] = XMFLOAT4(InputWaveDirection[i], time, 1.f, 1.f);

	}
	deviceContext->Unmap(SeaBuffer, 0);
	deviceContext->DSSetConstantBuffers(1, 1, &SeaBuffer);

	

}


