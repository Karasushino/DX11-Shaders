// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{

}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);



	// Create Mesh object and shader object
	mesh = new TessellationMesh(renderer->getDevice(), renderer->getDeviceContext());
	CubeShadow = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());


	planeMesh = new QuadPlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);
	waterPlaneMesh = new QuadPlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);

	PlaneShader = new HeightmapShader(renderer->getDevice(), hwnd);
	WaterShader = new TessellationShader(renderer->getDevice(), hwnd);
	DepthHeightmapShader = new DepthShaderHeightmap(renderer->getDevice(), hwnd);
	depthShader = new DepthShader(renderer->getDevice(), hwnd);
	textureShader = new TextureShader(renderer->getDevice(), hwnd);


	EdgeTesellation = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	InsideTesellation = XMFLOAT2(1.0f, 1.0f);

	textureMgr->loadTexture(L"brick", L"res/Moss0.jpg");
	textureMgr->loadTexture(L"height", L"res/heightmap.jpg");
	textureMgr->loadTexture(L"water", L"res/water.jpg");
	amplitude = 20.0f;
	// Variables for defining shadow map
	int shadowmapWidth = 1024;
	int shadowmapHeight = 1024;
	int sceneWidth = 300;
	int sceneHeight = 100;
	//Lights
	//Create Directional Light.
	light[0] = new Light;
	light[0]->setAmbientColour(0.35f, 0.35f, 0.35f, 1.0f);
	light[0]->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light[0]->setDirection(0.7f, -0.5f, -1.f);
	light[0]->setPosition(0.f, -15.f, 15.f);


	light[0]->generateViewMatrix();


	depthmapDirectional = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	
	//Default Attenuation Factors
	//No attenuation for directional light
	// light[0]->setAttenuationFactors(XMFLOAT3(0.f, 0.0f, 0.0f));

	//Create PointLight 1.
	light[1] = new Light;
	light[1]->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	light[1]->setDiffuseColour(0.0f, 0.0f, 0.0f, 1.0f);
	light[1]->setPosition(20.0f, 10.0f, 20.0f);
	light[1]->setDirection(0.f, 0.f, 0.0f);

	//Default Attenuation Factors
	light[1]->setAttenuationFactors(XMFLOAT3(1.f, 0.175f, 0.0f));

	//Create PointLight 2.
	light[2] = new Light;
	light[2]->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	light[2]->setDiffuseColour(0.0f, .0f,0.0f, 1.0f);
	light[2]->setPosition(50.0f, 10.0f, 50.0f);
	light[2]->setDirection(0.f, 0.f, 0.0f);
	//Default Attenuation Factors
	light[2]->setAttenuationFactors(XMFLOAT3(1.f, 0.175f, 0.0f));

	//Initialize to defaults
	for (int i = 0; i < 3; i++)
	{
		WaveSettings[i].x = 0.6f;
		WaveSettings[i].y = 1.f;
		WaveSettings[i].w = 1.f;
		WaveSettings[i].z = 8.f;
		WaveDirection[i] = 30.f;
	}
	
	smolOrthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth / 4, screenHeight / 4, -screenWidth / 2.7, screenHeight / 2.7);
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.

}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	time += timer->getTime();
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}


	return true;
}

bool App1::render()
{
	
	depthPass();


	finalPass();

	return true;
}

void App1::depthPass()
{
	
		// Set the render target to be the render to texture.
	int sceneWidth = 300;
	int sceneHeight = 100; 
		depthmapDirectional->BindDsvAndSetNullRenderTarget(renderer->getDeviceContext());
		
		light[0]->generateOrthoMatrix((float)sceneWidth, (float)sceneHeight, 20.f, 50.f);
		XMMATRIX lightViewMatrix = light[0]->getViewMatrix();
		XMMATRIX lightProjectionMatrix = light[0]->getOrthoMatrix();

		XMMATRIX worldMatrix = renderer->getWorldMatrix();

		// Render terrain
		planeMesh->sendData(renderer->getDeviceContext());
		DepthHeightmapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix,amplitude,textureMgr->getTexture(L"height"));
		DepthHeightmapShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	    XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(50.0f, 15.f, 50.0f);

		//Render example cube
		CubeShadow->sendData(renderer->getDeviceContext());
		depthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
		depthShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());


		//XMVECTOR direction = XMVectorSet(0.f, 1.f, 0.f, 0.f);
		//worldMatrix = renderer->getWorldMatrix();

		//XMMATRIX scaleMatrix = XMMatrixScaling(0.5f, 0.5f, 0.5f);
		//worldMatrix = XMMatrixMultiply(worldMatrix, scaleMatrix);
		//worldMatrix = XMMatrixTranslation(0.f, 7.f, 5.f);
		//// Render model
		//model->sendData(renderer->getDeviceContext());
		//depthShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
		//depthShader->render(renderer->getDeviceContext(), model->getIndexCount());

		// Set back buffer as render target and reset view port.
		renderer->setBackBufferRenderTarget();
		renderer->resetViewport();

	



}

void App1::finalPass()
{

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	


	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();


	XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(50.0f, 15.f, 50.0f);

	//CubeShadow->sendData(renderer->getDeviceContext());
	//textureShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	//textureShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());


	// Send geometry data, set shader parameters, render object with shader
	planeMesh->sendData(renderer->getDeviceContext());
	PlaneShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, EdgeTesellation, InsideTesellation, textureMgr->getTexture(L"brick"), camera->getPosition(),
		amplitude, textureMgr->getTexture(L"height"), light, depthmapDirectional->getDepthMapSRV());
	
	PlaneShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	


	XMMATRIX waterWorldMatrix = worldMatrix * XMMatrixTranslation(0.0f, Sealevel, 0.0f);
	waterPlaneMesh->sendData(renderer->getDeviceContext());

	renderer->setAlphaBlending(1);
	WaterShader->setShaderParameters(renderer->getDeviceContext(), waterWorldMatrix, viewMatrix, projectionMatrix, EdgeTesellation, InsideTesellation, camera->getPosition(),
		WaveSettings, textureMgr->getTexture(L"height"), WaveDirection, time);
	WaterShader->render(renderer->getDeviceContext(), waterPlaneMesh->getIndexCount());
	renderer->setAlphaBlending(0);



	//smolOrthoMesh->sendData(renderer->getDeviceContext());
	//XMMATRIX orthoMatrix = renderer->getOrthoMatrix();
	//XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix();
	//textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, depthmapDirectional->getDepthMapSRV());
	//textureShader->render(renderer->getDeviceContext(), smolOrthoMesh->getIndexCount());



	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();


	

	//return true;
}


void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("FPS: %.2f", time);
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	ImGui::SliderFloat("Tesellation Scalar", &EdgeTesellation.x, 1.0f, 20.0f);
	ImGui::SliderFloat("Amplitude Heightmap", &amplitude, 1.0f, 100.0f);

	ImGui::SliderFloat("Wave Amplitude", &WaveSettings[0].y, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave Frequency: ", &WaveSettings[0].z, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave Speed: ", &WaveSettings[0].w, 1.0f, 20.0f);
	//Smootheness
	//Direction Vector
	ImGui::SliderAngle("Wave Direction: ", &WaveDirection[0], 0.0f, 360.0f);
	ImGui::SliderFloat("Wave Smoothness: ", &WaveSettings[0].x, 0.0f, 1.0f);
	
	ImGui::SliderFloat("Wave 2 Amplitude", &WaveSettings[1].y, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave 2 Frequency: ", &WaveSettings[1].z, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave 2 Speed: ", &WaveSettings[1].w, 1.0f, 20.0f);
	//Smootheness
	//Direction Vector
	ImGui::SliderAngle("Wave 2 Direction: ", &WaveDirection[1], 0.0f, 360.0f);
	ImGui::SliderFloat("Wave 2 Smoothness: ", &WaveSettings[1].x, 0.0f, 1.0f);


	ImGui::SliderFloat("Wave 3 Amplitude", &WaveSettings[2].y, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave 3 Frequency: ", &WaveSettings[2].z, 1.0f, 20.0f);
	ImGui::SliderFloat("Wave 3 Speed: ", &WaveSettings[2].w, 1.0f, 20.0f);
	//Smootheness
	//Direction Vector
	ImGui::SliderAngle("Wave 3 Direction: ", &WaveDirection[2], 0.0f, 360.0f);
	ImGui::SliderFloat("Wave 3 Smoothness: ", &WaveSettings[2].x, 0.0f, 1.0f);

	ImGui::SliderFloat("Sea Level: ", &Sealevel, -10.0f, 10.0f);


	ImGui::SliderFloat3("PEpega light thing:", direction, -1.f, 1.f);
	light[0]->setDirection(direction[0], direction[1], direction[2]);

	ImGui::SliderFloat("PEpega light c", &diff[0], 0.f, 100.f);
	light[0]->setDiffuseColour(diff[0], diff[0], diff[0],1.f);


	ImGui::SliderFloat3("light position:", position, -50.f, 50.f);
	light[0]->setPosition(position[0], position[1], position[2]);



	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

