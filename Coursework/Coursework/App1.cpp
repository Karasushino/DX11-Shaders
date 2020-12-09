// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{

}
void App1::style()
{
	//imGuiIO.Fonts->AddFontFromFileTTF("../data/Fonts/Ruda-Bold.ttf", 15.0f, &config);
	ImGui::GetStyle().FrameRounding = 4.0f;
	ImGui::GetStyle().GrabRounding = 4.0f;

	ImGuiStyle* style = &ImGui::GetStyle();

	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	//colors[ImguiCol_tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	//colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	//colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
	//colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	//colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	style->FramePadding = ImVec2(4, 2);
	style->ItemSpacing = ImVec2(10, 15);
	style->IndentSpacing = 12;
	style->ScrollbarSize = 10;

	style->WindowRounding = 4;
	style->FrameRounding = 5;
	style->PopupRounding = 5;
	style->ScrollbarRounding = 6;
	style->GrabRounding = 4;
	



}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);
	style();


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
	grassShader = new GeometryShader(renderer->getDevice(), hwnd);
	cubeShader = new LightedTextureShader(renderer->getDevice(), hwnd);
	depthFieldShader = new DepthOfFieldShader(renderer->getDevice(), hwnd);


	grassShaderDepth = new GeometryShaderDepth(renderer->getDevice(), hwnd);

	grassMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);

	//EdgeTesellation = XMFLOAT4(1.0f, 1.0f, 1.0f,1.0f);
	//InsideTesellation = XMFLOAT2(1.0f, 1.0f);

	textureMgr->loadTexture(L"WindMap", L"res/WaterDistortion.png");
	textureMgr->loadTexture(L"moss", L"res/Moss0.jpg");
	textureMgr->loadTexture(L"Bunny", L"res/bunny.png");
	textureMgr->loadTexture(L"height", L"res/height.jpg");
	textureMgr->loadTexture(L"height2", L"res/height.png");
	textureMgr->loadTexture(L"water", L"res/water.jpg");
	textureMgr->loadTexture(L"Noise", L"res/noise.jpg");
	textureMgr->loadTexture(L"GrassSpawn", L"res/grassNoise.jpg");

	amplitude = 20.0f;
	// Variables for defining shadow map
	int shadowmapWidth = 2048;
	int shadowmapHeight = 2048;
	int sceneWidth = 200;
	int sceneHeight = 200;
	//Lights
	//Create Directional Light.
	directionalLight = new Light;
	directionalLight->setAmbientColour(0.35f, 0.35f, 0.35f, 1.0f);
	directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLight->setDirection(0.7f, -0.7f, 0.f);
	directionalLight->setPosition(50.f, 15.f, 50.f);
	directionalLight->generateViewMatrix();
	directionalLight->generateOrthoMatrix((float)sceneWidth, (float)sceneHeight, 2.f, 100.f);




	depthmapDirectional = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	cameraDepthMap = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	
	//Initialize all shadowmaps
	for (size_t i = 0; i < numberOfPointlights*6; i++)
	{
		pointlightShadows[i] = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	}


	//Default Attenuation Factors
	//No attenuation for directional light
	// light[0]->setAttenuationFactors(XMFLOAT3(0.f, 0.0f, 0.0f));

	//Create PointLight 1.
	pointlight[0] = new Light;
	pointlight[0]->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	pointlight[0]->setDiffuseColour(0.4f, 0.4f, 0.4f, 1.0f);
	pointlight[0]->setPosition(20.0f, 10.0f, 20.0f);
	pointlight[0]->setDirection(1.f, 1.f, 1.0f);
	pointlight[0]->generateProjectionMatrix(2.f, 100.f);
	//Default Attenuation Factors
	pointlight[0]->setAttenuationFactors(XMFLOAT3(1.f, 0.175f, 0.0f));

	//Create PointLight 2.
	pointlight[1] = new Light;
	pointlight[1]->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	pointlight[1]->setDiffuseColour(0.0f, .0f,0.0f, 1.0f);
	pointlight[1]->setPosition(50.0f, 10.0f, 50.0f);
	pointlight[1]->setDirection(1.f, 1.f, 1.0f);
	pointlight[1]->generateProjectionMatrix(4.f, 100.f);
	//Default Attenuation Factors
	pointlight[1]->setAttenuationFactors(XMFLOAT3(1.f, 0.175f, 0.0f));


	
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
	orthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth, screenHeight);	// Full screen size
	downSampleOrthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth/ 1.2f, screenHeight/ 1.2f); //downsample ortho

	//Render Texture
	renderTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	//Post processing render textures
	horizontalBlurredSceneTexture = new RenderTexture(renderer->getDevice(), screenWidth/1.2f, screenHeight/ 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
	verticalBlurredSceneTexture = new RenderTexture(renderer->getDevice(), screenWidth/ 1.2f, screenHeight/ 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
	upsampleTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	downSampleTexture = new RenderTexture(renderer->getDevice(), screenWidth/ 1.2f, screenHeight/ 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
	depthOfFieldTexture = new RenderTexture(renderer->getDevice(), screenWidth / 1.2f, screenHeight / 1.2f, SCREEN_NEAR, SCREEN_DEPTH);

	//Post Processing Shaders
	horizontalBlurShader = new HorizontalBlurShader(renderer->getDevice(), hwnd);
	verticalBlurShader = new VerticalBlurShader(renderer->getDevice(), hwnd);
	depthFieldShader = new DepthOfFieldShader(renderer->getDevice(), hwnd);


	//Depth of Field parameters
	//Distance Focus
	DepthFieldSettings.x = 0.f;
	//Focus Range
	DepthFieldSettings.y = 6.7f;
	//Close plane
	DepthFieldSettings.z = 9.3f;
	//Far plane
	DepthFieldSettings.w = 32.0;
}



App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.

}

ID3D11ShaderResourceView* App1::getTerrainHeigthmap()
{
	ID3D11ShaderResourceView* heightmap = nullptr;

	switch (selectedHeightmap)
	{
	case 0:
		heightmap = textureMgr->getTexture(L"height");
		break;

	case 1:
		heightmap = textureMgr->getTexture(L"height2");
		break;
	default:
		break;
	}

	return heightmap;
}

ID3D11ShaderResourceView* App1::getTerrainTexture()
{
	ID3D11ShaderResourceView* texture = nullptr;

	switch (selectedTexture)
	{
	case 0:
		texture = textureMgr->getTexture(L"moss");
		break;

	case 1:
		texture = textureMgr->getTexture(L"Bunny");
		break;
	default:
		break;
	}

	return texture;
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
	//Depth Passes
	depthPass();
	cameraDepthPass();
	pointlightDepthPass();
	//Render the scene
	firstPass();

	//If postprocessing is on do.
	if (togglePostprocess)
	{
		//Post Processing
		downsample();

		//Render scene to texture
		horizontalBlur();
		verticalBlur();
		depthOfFieldPass();

		//Upsample all post processing
		upSampleTexture();
	}
	

	//Render the scene for the user
	finalPass();


	return true;
}

void App1::depthPass()
{
	
		depthmapDirectional->BindDsvAndSetNullRenderTarget(renderer->getDeviceContext());
		 
		directionalLight->generateViewMatrix();

		XMMATRIX lightViewMatrix = directionalLight->getViewMatrix();
		XMMATRIX lightProjectionMatrix = directionalLight->getOrthoMatrix();

		XMMATRIX worldMatrix = renderer->getWorldMatrix();

		// Render terrain
		planeMesh->sendData(renderer->getDeviceContext());
		DepthHeightmapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix,amplitude, getTerrainHeigthmap());
		DepthHeightmapShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	    XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(ballposition[0],ballposition[1],ballposition[2]);

		//Render example cube
		CubeShadow->sendData(renderer->getDeviceContext());
		depthShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, lightViewMatrix, lightProjectionMatrix);
		depthShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());


		// Render terrain
		grassMesh->sendData(renderer->getDeviceContext());
		grassShaderDepth->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, textureMgr->getTexture(L"WindMap"), time, getTerrainHeigthmap(),
			textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude);
		grassShaderDepth->render(renderer->getDeviceContext(), grassMesh->getIndexCount());


		// Set back buffer as render target and reset view port.
		renderer->setBackBufferRenderTarget();
		renderer->resetViewport();


}

void App1::cameraDepthPass()
{
    cameraDepthMap->BindDsvAndSetNullRenderTarget(renderer->getDeviceContext());

	XMMATRIX camViewMatrix = camera->getViewMatrix();
	XMMATRIX camProjectionMatrix = renderer->getProjectionMatrix();

	XMMATRIX worldMatrix = renderer->getWorldMatrix();

	// Render terrain
	planeMesh->sendData(renderer->getDeviceContext());
	DepthHeightmapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, camViewMatrix, camProjectionMatrix, amplitude, getTerrainHeigthmap());
	DepthHeightmapShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(ballposition[0], ballposition[1], ballposition[2]);

	//Render example cube
	CubeShadow->sendData(renderer->getDeviceContext());
	depthShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, camViewMatrix, camProjectionMatrix);
	depthShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());

	// Render terrain
	grassMesh->sendData(renderer->getDeviceContext());
	grassShaderDepth->setShaderParameters(renderer->getDeviceContext(), worldMatrix, camViewMatrix, camProjectionMatrix, textureMgr->getTexture(L"WindMap"), time, getTerrainHeigthmap(),
		textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude);
	grassShaderDepth->render(renderer->getDeviceContext(), grassMesh->getIndexCount());


	// Set back buffer as render target and reset view port.
	renderer->setBackBufferRenderTarget();
	renderer->resetViewport();

}

void App1::pointlightDepthPass()
{
	int indexPointlight = 0;

	//Loop for number of pointlights
	for (size_t i = 0; i < numberOfPointlights; i++)
	{
		//Loop for 6 directions
		for (int z = 0; z < 6; z++)
		{
			
			// Set the render target to be the render to texture.
			pointlightShadows[indexPointlight]->BindDsvAndSetNullRenderTarget(renderer->getDeviceContext());

			//Set the directions using array from the header
			pointlight[i]->setDirection(directions[z].x, directions[z].y, directions[z].z);
			pointlight[i]->generateViewMatrix();

			XMMATRIX lightViewMatrix = pointlight[i]->getViewMatrix();

			//Store the view on array to pass to GPU
			pointlightView[indexPointlight] = lightViewMatrix;
			//Should be the same for every different light
			XMMATRIX lightProjectionMatrix = pointlight[i]->getProjectionMatrix();

			XMMATRIX worldMatrix = renderer->getWorldMatrix();

			//Render terrain for Depth map
			planeMesh->sendData(renderer->getDeviceContext());
			DepthHeightmapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, amplitude, getTerrainHeigthmap());
			DepthHeightmapShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

			//Move the geometry
			XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(ballposition[0], ballposition[1], ballposition[2]);

			//Render example sphere
			CubeShadow->sendData(renderer->getDeviceContext());
			depthShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, lightViewMatrix, lightProjectionMatrix);
			depthShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());
			

			// Render terrain
			grassMesh->sendData(renderer->getDeviceContext());
			grassShaderDepth->setShaderParameters(renderer->getDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix, textureMgr->getTexture(L"WindMap"), time, getTerrainHeigthmap(),
				textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude);
			grassShaderDepth->render(renderer->getDeviceContext(), grassMesh->getIndexCount());


			// Set back buffer as render target and reset view port.
			renderer->setBackBufferRenderTarget();
			renderer->resetViewport();

			//Store generated depth map on array
			pointlightDepthTextures[indexPointlight] = pointlightShadows[indexPointlight]->getDepthMapSRV();

			//Increment index to set next array index
			indexPointlight++;
		}
	}
}

void App1::firstPass()
{

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	//renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Set the render target to be the render to texture and clear it
	renderTexture->setRenderTarget(renderer->getDeviceContext());
	renderTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();


	//Toggle wiregrame mode only for this portion
	renderer->setWireframeMode(wireframe);

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();


	if (renderPlane)
	{

		// Send geometry data, set shader parameters, render object with shader
		planeMesh->sendData(renderer->getDeviceContext());
		PlaneShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix,TesellationFactor, getTerrainTexture(), camera->getPosition(),
		amplitude, getTerrainHeigthmap(), directionalLight, pointlight, depthmapDirectional->getDepthMapSRV(), pointlightDepthTextures,pointlightView,textureTiling);
	
		PlaneShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());
	}


	if (renderGrass)
	{
		renderer->setNoCullMode(true);
		grassMesh->sendData(renderer->getDeviceContext(), D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
		grassShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"WindMap"), getTerrainHeigthmap(),
			textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude, directionalLight, depthmapDirectional->getDepthMapSRV());

		grassShader->setPixelShaderParameters(renderer->getDeviceContext(), bottomGrassColor, topGrassColor);
		grassShader->setHullshaderParameters(renderer->getDeviceContext(), grassDensity);
		grassShader->setGeometryShaderParameters(renderer->getDeviceContext(), grassMaxHeight, grassWidth, windStrength, windFrequency, time);


		grassShader->render(renderer->getDeviceContext(), grassMesh->getIndexCount());
		renderer->setNoCullMode(false);
	}

	if (renderWater)
	{
		XMMATRIX waterWorldMatrix = worldMatrix * XMMatrixTranslation(0.0f, Sealevel, 0.0f);
		waterPlaneMesh->sendData(renderer->getDeviceContext());
		renderer->setAlphaBlending(1);
		XMFLOAT2 tes = XMFLOAT2(TesellationFactor.x,TesellationFactor.y);
		WaterShader->setShaderParameters(renderer->getDeviceContext(), waterWorldMatrix, viewMatrix, projectionMatrix, TesellationFactor, tes, camera->getPosition(),
		WaveSettings, WaveDirection, time);
		WaterShader->setPixelShaderParameters(renderer->getDeviceContext(), waterOffset, depthScalar, Sealevel, amplitude, deepColor,shallowColor, getTerrainHeigthmap());
		WaterShader->setHullShaderParameters(renderer->getDeviceContext(), tessellationFactor, dynamicTessellationFactor,
			dynamicTessellationToggle, dystanceScalar);
		WaterShader->render(renderer->getDeviceContext(), waterPlaneMesh->getIndexCount());
		renderer->setAlphaBlending(0);
	}

	
	////Debuging window
	//smolOrthoMesh->sendData(renderer->getDeviceContext());
	//XMMATRIX orthoMatrix = renderer->getOrthoMatrix();
	//XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix();
	//textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, depthmapDirectional->getDepthMapSRV());
	//textureShader->render(renderer->getDeviceContext(), smolOrthoMesh->getIndexCount());

	XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(ballposition[0], ballposition[1], ballposition[2]);
	CubeShadow->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	textureShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());

	

	//Set it always to walse so it doens't get beyond this point and wareframe render textures
	renderer->setWireframeMode(false);
	// Swap the buffers
	renderer->setBackBufferRenderTarget();

	//renderer->endScene();


	

	//return true;
}

void App1::downsample()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;


	downSampleTexture->setRenderTarget(renderer->getDeviceContext());
	downSampleTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	//Don't clear, overwrite the horizontal blured one.
	//blurredScene->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = downSampleTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	downSampleOrthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, renderTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), downSampleOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);
	//verticalBlurredSceneTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 0.0f, 0.0f, 1.0f);
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();

}

void App1::horizontalBlur()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;


	horizontalBlurredSceneTexture->setRenderTarget(renderer->getDeviceContext());
	horizontalBlurredSceneTexture->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	XMFLOAT2 screenSize = XMFLOAT2(horizontalBlurredSceneTexture->getTextureWidth(), horizontalBlurredSceneTexture->getTextureHeight());



	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = horizontalBlurredSceneTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	downSampleOrthoMesh->sendData(renderer->getDeviceContext());
	horizontalBlurShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, downSampleTexture->getShaderResourceView(), screenSize.x/4);
	horizontalBlurShader->render(renderer->getDeviceContext(), downSampleOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::verticalBlur()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	XMFLOAT2 screenSize = XMFLOAT2(verticalBlurredSceneTexture->getTextureWidth(), verticalBlurredSceneTexture->getTextureHeight());

	verticalBlurredSceneTexture->setRenderTarget(renderer->getDeviceContext());
	verticalBlurredSceneTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	//Don't clear, overwrite the horizontal blured one.
	//blurredScene->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = verticalBlurredSceneTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	downSampleOrthoMesh->sendData(renderer->getDeviceContext());
	verticalBlurShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, horizontalBlurredSceneTexture->getShaderResourceView(), screenSize.y/4);
	verticalBlurShader->render(renderer->getDeviceContext(), downSampleOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);
	//verticalBlurredSceneTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 0.0f, 0.0f, 1.0f);
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::depthOfFieldPass()
{
	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	XMFLOAT2 screenSize = XMFLOAT2(depthOfFieldTexture->getTextureWidth(), depthOfFieldTexture->getTextureHeight());

	depthOfFieldTexture->setRenderTarget(renderer->getDeviceContext());
	depthOfFieldTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	//Don't clear, overwrite the horizontal blured one.
	//blurredScene->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = depthOfFieldTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	downSampleOrthoMesh->sendData(renderer->getDeviceContext());
	depthFieldShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, downSampleTexture->getShaderResourceView(),
		verticalBlurredSceneTexture->getShaderResourceView(),cameraDepthMap->getDepthMapSRV(),DepthFieldSettings);
	depthFieldShader->render(renderer->getDeviceContext(), downSampleOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);
	//verticalBlurredSceneTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 0.0f, 0.0f, 1.0f);
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::upSampleTexture()
{

	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;


	upsampleTexture->setRenderTarget(renderer->getDeviceContext());
	upsampleTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	//Don't clear, overwrite the horizontal blured one.
	//blurredScene->clearRenderTarget(renderer->getDeviceContext(), 0.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = upsampleTexture->getOrthoMatrix();

	// Render for Vertical Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, depthOfFieldTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);
	
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();

}

void App1::finalPass()
{
	
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	/*Checks if the post processing stage is on, if it is it will get the processed texture, if it isn't it will just get
	the render texture from the 1st pass*/
	ID3D11ShaderResourceView* finalRender;
	if (togglePostprocess)
		finalRender = upsampleTexture->getShaderResourceView();
	else
		finalRender = renderTexture->getShaderResourceView();



	// RENDER THE RENDER TEXTURE SCENE
	// Requires 2D rendering and an ortho mesh.
	renderer->setZBuffer(false);
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX orthoMatrix = renderer->getOrthoMatrix();  // ortho matrix for 2D rendering
	XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix(); // Default camera position for orthographic rendering
	orthoMesh->sendData(renderer->getDeviceContext()); 
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, finalRender);
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);


	

	// Render GUI
	gui();
	// Present the rendered scene to the screen.
	renderer->endScene();
}


void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);
	ImGui::BeginMainMenuBar();
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("Time elapsed: %.2f", time);
	ImGui::Checkbox("Wireframe mode", &wireframe);
	ImGui::EndMainMenuBar();


	
	ImGui::Begin("Shader Settings");
	ImGui::TextWrapped("Click on the buttons to open their settings."); 

	
	//Water bool
	static bool mizu = false;
	ImGuiFunctions::ToggleButton(ImGui::Button("Water", ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)), &mizu);
	ImGui::SameLine();
	ImGui::Checkbox("", &renderWater);
	// Water settings window
	if (mizu)
	{
		ImGui::Begin("Water Settings", &mizu);

		//Resizes slider
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.40f);

		//Move the plane up or down
		ImGui::SliderFloat("Water Level", &Sealevel, -20.0f, 20.0f);
		

		//Header for the settings of Wave 1
		if(ImGui::CollapsingHeader("Wave 1 Settings"))
		{
			ImGui::SliderFloat("Wave Amplitude", &WaveSettings[0].y, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave Frequency: ", &WaveSettings[0].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave Speed: ", &WaveSettings[0].w, 1.0f, 20.0f);
			//Smootheness
		//Direction Vector
			ImGui::SliderAngle("Wave Direction: ", &WaveDirection[0], 0.0f, 360.0f);
			ImGui::SliderFloat("Wave Smoothness: ", &WaveSettings[0].x, 0.0f, 1.0f);
		}
		ImGui::Separator();

		//Header for the settings of Wave 2
		if (ImGui::CollapsingHeader("Wave 2 Settings"))
		{
			ImGui::SliderFloat("Wave 2 Amplitude", &WaveSettings[1].y, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 2 Frequency: ", &WaveSettings[1].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 2 Speed: ", &WaveSettings[1].w, 1.0f, 20.0f);
			//Smootheness
			//Direction Vector
			ImGui::SliderAngle("Wave 2 Direction: ", &WaveDirection[1], 0.0f, 360.0f);
			ImGui::SliderFloat("Wave 2 Smoothness: ", &WaveSettings[1].x, 0.0f, 1.0f);
			
		}
		ImGui::Separator();

		//Header for the settings of Wave 3
		if (ImGui::CollapsingHeader("Wave 3 Settings"))
		{
			
			ImGui::SliderFloat("Wave 3 Amplitude", &WaveSettings[2].y, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 3 Frequency: ", &WaveSettings[2].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 3 Speed: ", &WaveSettings[2].w, 1.0f, 20.0f);
			//Smootheness
			//Direction Vector
			ImGui::SliderFloat("Wave 3 Direction: ", &WaveDirection[2], 0.0f, 360.0f);
			ImGui::SliderFloat("Wave 3 Smoothness: ", &WaveSettings[2].x, 0.0f, 1.0f);
			
		}
		ImGui::Separator();

		//Header for the settings of water depth
		if (ImGui::CollapsingHeader("Water Depth Color"))
		{
			ImGui::ColorEdit4("Deep Water Color", deepColor, ImGuiColorEditFlags_NoInputs);
			ImGui::ColorEdit4("Shallow Water Color", shallowColor, ImGuiColorEditFlags_NoInputs);

			ImGui::SliderFloat("Water Depth Scalar", &depthScalar, 0.f, 40.f);
			ImGui::SliderFloat("Offset Depth", &waterOffset, 0.f, 15.f);
		}
		ImGui::Separator();

		//Header for the settings of water tessellation
		if (ImGui::CollapsingHeader("Water Tessellation"))
		{
			ImGui::Checkbox("Dynamic Tessellation", &dynamicTessellationToggle);
			if (dynamicTessellationToggle)
			{
				ImGui::SliderFloat("Dynamic Factor", &dynamicTessellationFactor, 0, 15);
				ImGui::SliderFloat("Distance Scalar", &dystanceScalar, 1, 150);
			}
			else
				ImGui::SliderFloat("Tessellation Factor", &tessellationFactor,0,25);

			//ImGui::SliderFloat("Tessellation Factor", &TesellationFactor.x, 1.0f, 25.0f);

		}
		ImGui::Separator();
		ImGui::End();
	}
	
	//Terrain bool window
	static bool terrain = false;
	ImGuiFunctions::ToggleButton(ImGui::Button("Terrain",ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)), &terrain);
	ImGui::SameLine();
	ImGui::Checkbox("##1", &renderPlane);
	if (terrain)
	{
		ImGui::Begin("Terrain Settings", &terrain);

		static const char* selectedItem = heightmapsLabel[0];
		//Drop down combo menu to select the heightmap to use
		if (ImGui::BeginCombo("Heightmaps", selectedItem))
		{
			for (int i = 0; i < IM_ARRAYSIZE(heightmapsLabel); i++)
			{
				bool isSelected = (selectedItem == heightmapsLabel[i]);
				if (ImGui::Selectable(heightmapsLabel[i], isSelected))
				{
					selectedItem = heightmapsLabel[i];
					selectedHeightmap = i;
				}
					
				if (isSelected)
				{
					
					ImGui::SetItemDefaultFocus();
					
				}
				
			}
			ImGui::EndCombo();
		}

		//Drop down combo menu to select the texture to use

		static const char* selectedItemT = textureLabel[0];
		if (ImGui::BeginCombo("Textures", selectedItemT))
		{
			for (int i = 0; i < IM_ARRAYSIZE(textureLabel); i++)
			{
				bool isSelected = (selectedItemT == textureLabel[i]);
				if (ImGui::Selectable(textureLabel[i], isSelected))
				{
					selectedItemT = textureLabel[i];
					selectedTexture = i;
				}

				if (isSelected)
				{

					ImGui::SetItemDefaultFocus();

				}

			}
			ImGui::EndCombo();
		}

		//Resizes slider
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.40f);
		
		ImGui::SliderFloat("Tiling Factor", &textureTiling, 1.0f, 25.0f);
		ImGui::SliderFloat("Tessellation Factor", &TesellationFactor.x, 1.0f, 25.0f);

		ImGui::SliderFloat("Amplitude Heightmap", &amplitude, 1.0f, 100.0f);
		ImGui::End();
	}
	
	//Lighting bool window
	static bool lighting = false;
	ImGuiFunctions::ToggleButton(ImGui::Button("Lighting",ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)), &lighting);
	if (lighting)
	{
		ImGui::Begin("Lighting Settings", &lighting);
		//Resizes slider
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.40f);

		static bool dirlight = true;
		static bool pointlightsOff = false;
		ImGui::ColorEdit4("Ambient Light Color", ambientLight, ImGuiColorEditFlags_NoInputs);
		ImGui::Checkbox("Directional Light", &dirlight);
		directionalLight->setAmbientColour(ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3]);


		if (!dirlight)
			directionalLight->setDiffuseColour(0, 0, 0, 1.f);
		else
			directionalLight->setDiffuseColour(directionalDiffuse[0], directionalDiffuse[1], directionalDiffuse[2], 1.f);

		if (ImGui::CollapsingHeader("Directional Light Settings"))
		{
			//Lighting bool window
			ImGui::ColorEdit4("Directional Diffuse", directionalDiffuse, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

			if(dirlight)
			directionalLight->setDiffuseColour(directionalDiffuse[0], directionalDiffuse[1], directionalDiffuse[2], 1.f);

			directionalLight->setDirection(direction[0], direction[1], direction[2]);
			ImGui::SameLine(); ImGui::Text("Directional Diffuse Color Picker"); 
			ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");

			//This is temporal, will be changed to SliderAngle and calculate vectors on Shader from the angle inputed
			ImGui::SliderFloat3("Directional Light Direction:", direction, -1.f, 1.f);
			if (direction[0] == 0.0f)
				direction[0] = 0.000001;
			if (direction[1] == 0.0f)
				direction[1] = 0.000001;

			

			ImGui::SliderFloat3("Directional Light Position:", position, -50.f, 50.f);
			directionalLight->setPosition(position[0], position[1], position[2]);
		
		}
		


		ImGui::Separator();
		

		
			
		ImGui::SliderFloat3("Pointlight 1 Position:", pointPosition, -120.f, 120.f);
		pointlight[0]->setPosition(pointPosition[0], pointPosition[1], pointPosition[2]);

		ImGui::ColorEdit4("Pointlight Diffuse", pointlightDiffuse, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
		pointlight[0]->setDiffuseColour(pointlightDiffuse[0], pointlightDiffuse[1], pointlightDiffuse[2], 1.f);


		ImGui::SameLine(); ImGui::Text("Pointlight Diffuse Color Picker");
		ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");

		ImGui::SliderFloat3("Pointlight Attenuation", att, 0.f, 1.f);


		ImGui::SliderFloat3("Sphere position:", ballposition, -50.f, 50.f);

		pointlight[0]->setAttenuationFactors(XMFLOAT3(att[0], att[1], att[2]));
		ImGui::End();
	}

	//Postprocessing bool window
	static bool postprocessing = false;
	ImGuiFunctions::ToggleButton(ImGui::Button("Postprocessing", ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)), &postprocessing);
	ImGui::SameLine();
	ImGui::Checkbox("##2", &togglePostprocess);
	if (postprocessing)
	{
		ImGui::Begin("Postprocessing Settings", &postprocessing);

		ImGui::TextColored(ImVec4(0.149, 1, 0.078,1),"Depth of Field");
		ImGui::SliderFloat("Focus Range", &DepthFieldSettings.y, 0.f, 15.f);
		ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("A scalar that determines the range where blur will start, higher value makes it further from the camera.");

		ImGui::SliderFloat("Close plane", &DepthFieldSettings.z, 0.f, 15.f);
		ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Changes the width of the area to be blurred, bigger value creates a wider area.");

		ImGui::SliderFloat("Far plane", &DepthFieldSettings.w, 1.f, 150.f);
		ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Moves the area to blur closer or further from the camera, smaller makes it further from it.");

		ImGui::End();
	}

	//Postprocessing bool window
	static bool grass = false;
	ImGuiFunctions::ToggleButton(ImGui::Button("Grass", ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)), &grass);
	ImGui::SameLine();
	ImGui::Checkbox("##3", &renderGrass);
	if (grass)
	{
		ImGui::Begin("Grass Settings", &grass);
		//Resizes slider
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.40f);
		ImGui::ColorEdit4("Bottom Grass Color", bottomGrassColor, ImGuiColorEditFlags_NoInputs);
		ImGui::ColorEdit4("Top Grass Color", topGrassColor, ImGuiColorEditFlags_NoInputs);
		ImGui::Separator();
		ImGui::SliderFloat("Grass Density", &grassDensity,1,20);
		ImGui::SliderFloat("Grass Max Height", &grassMaxHeight, 1, 4);
		ImGui::SliderFloat("Grass Width", &grassWidth, 0.2f, 5);
		ImGui::SliderFloat("Wind Strength", &windStrength, 1, 3);
		ImGui::SliderFloat("Wind Frequency", &windFrequency, 0.f, 0.2f);

		ImGui::End();

	}

	ImGui::End();
	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

