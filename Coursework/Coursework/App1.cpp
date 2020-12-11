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
	// Call Super Init Function (Required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	//Initialize Custom ImGui Style (from github)
	style();

	//Scene Height and Width
	int sceneWidth = 200;
	int sceneHeight = 200;


	//Default Camera Position
	camera->setPosition(8.60f, 22.67f, 102.63f);
	camera->setRotation(6.f, 142.f, 0.f);

	//Texture Loading function calls
	#pragma region All Texture Loading

	//Terrain Heightmap Textures
	textureMgr->loadTexture(L"LakeHeight", L"res/lakesheight.jpg");
	textureMgr->loadTexture(L"CliftHeight", L"res/cliftsheight.jpg");
	textureMgr->loadTexture(L"CoastHeight", L"res/coastheight.jpg");
	textureMgr->loadTexture(L"height", L"res/height.jpg"); //The provided Default heightmap

	//Terrain Color Textures
	textureMgr->loadTexture(L"CliftTexture", L"res/cliftsTexture.jpg");
	textureMgr->loadTexture(L"CoastTexture", L"res/coastTexture.jpg");
	textureMgr->loadTexture(L"LakeTexture", L"res/lakesTexture.jpg");
	textureMgr->loadTexture(L"moss", L"res/Moss0.jpg"); //Extra optional generic texture.

	//DuDv map for grass sway
	textureMgr->loadTexture(L"WindMap", L"res/dudvmap.jpg");
	

	
	 //Noise map for Rotation of grass.
	textureMgr->loadTexture(L"Noise", L"res/noise.jpg");
	textureMgr->loadTexture(L"GrassSpawn", L"res/grassNoise.jpg");
	#pragma endregion

	//Basic Geometry and Basic Shaders (Including Pointlight Gyzmos)
	#pragma region Basic Shaders and Geometry

	// Create the sphere object use to demostrate shadows working.
	CubeShadow = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());

	//Objects
	//Pointlight Gyzmo mesh of pointlight 1
	pointlightGyzmos1 = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext(), 5);
	//Pointlight Gyzmo mesh of pointlight 2
	pointlightGyzmos2 = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext(), 5);

	//Shaders
	//Basic Depth shader for any simple geometry.
	depthShader = new DepthShader(renderer->getDevice(), hwnd);
	//Simple Shader that renders basic geometry with a texture.
	textureShader = new TextureShader(renderer->getDevice(), hwnd);


	#pragma endregion

	//Terrain Shaders and Geometry
	#pragma region Terrain Initializations

	//The plane of the Terrain
	planeMesh = new QuadPlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);
	
	//Shader used for the Terrain, using a heightmap.
	PlaneShader = new HeightmapShader(renderer->getDevice(), hwnd);
	
	//Optimized shader using only relevant data to render geometry of the terrain for a depth pass.
	DepthHeightmapShader = new DepthShaderHeightmap(renderer->getDevice(), hwnd);
	
	#pragma endregion
	
	//Post Processing Shaders, Rendertextures and ortomeshes
	#pragma region Post Processing Initializations

	//Main Render Texture of Scene
	renderTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

		//All Rendertextures and Orthomeshes initializations
		#pragma region Orthomeshes and RenderTextures
		//Orthomeshes for Post Processing
		orthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth, screenHeight);	// Full screen size
		downSampleOrthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth / 1.2f, screenHeight / 1.2f); //Downsample ortho


		//Post processing render Textures
		horizontalBlurredSceneTexture = new RenderTexture(renderer->getDevice(), screenWidth / 1.2f, screenHeight / 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
		verticalBlurredSceneTexture = new RenderTexture(renderer->getDevice(), screenWidth / 1.2f, screenHeight / 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
		upsampleTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
		downSampleTexture = new RenderTexture(renderer->getDevice(), screenWidth / 1.2f, screenHeight / 1.2f, SCREEN_NEAR, SCREEN_DEPTH);
		depthOfFieldTexture = new RenderTexture(renderer->getDevice(), screenWidth / 1.2f, screenHeight / 1.2f, SCREEN_NEAR, SCREEN_DEPTH);

		//Post Processing Shaders
		horizontalBlurShader = new HorizontalBlurShader(renderer->getDevice(), hwnd);
		verticalBlurShader = new VerticalBlurShader(renderer->getDevice(), hwnd);
		depthFieldShader = new DepthOfFieldShader(renderer->getDevice(), hwnd);
		#pragma endregion

		//Default Depth of Field parameters
		#pragma region Default Depth of Field Values

		//Distance Focus
		DepthFieldSettings.x = 0.f;
		//Focus Range
		DepthFieldSettings.y = 6.7f;
		//Close plane
		DepthFieldSettings.z = 9.3f;
		//Far plane
		DepthFieldSettings.w = 32.0;

		#pragma endregion

	#pragma endregion

	//Water Shaders and Geometry
	#pragma region Water Shader Initializations
	//The plane of the Water
	waterPlaneMesh = new QuadPlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);
	//Shaders that uses Trochoidal waves to create realistic water simulation.
	WaterShader = new TessellationShader(renderer->getDevice(), hwnd);

	//Default values of the Waves.
		#pragma region Water Waves Defaults
		//1st wave
		WaveSettings[0].x = 1.f;
		WaveSettings[0].y = 1.0f;
		WaveSettings[0].z = 7.4f;
		WaveSettings[0].w = 1.f;

		//2nd Wave
		WaveSettings[1].x = 0.6f;
		WaveSettings[1].y = 1.0f;
		WaveSettings[1].z = 12.3f;
		WaveSettings[1].w = 0.6f;

		//3rd Wave
		WaveSettings[2].x = 0.6f;
		WaveSettings[2].y = 0.8f;
		WaveSettings[2].z = 8.5f;
		WaveSettings[2].w = 1.0f;
		#pragma endregion

	#pragma endregion

	//Grass Shaders and Geometry
	#pragma region Grass Shader Initializations

	//Plane of the Grass.
	grassMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext(), 120);

	//Optimized shader for depth pass calculation (not currectly working need to FIX)
	grassShaderDepth = new GeometryShaderDepth(renderer->getDevice(), hwnd);
	

	//Shader responsible of the Generation of the Grass plane. 
	grassShader = new GeometryShader(renderer->getDevice(), hwnd);

	#pragma endregion

	//Lights
	#pragma region Lighting Initialization and Defaults

	//Create Directional Light and set Defaults.
	directionalLight = new Light;
	directionalLight->setAmbientColour(0.35f, 0.35f, 0.35f, 1.0f);
	directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLight->setDirection(0.7f, -0.7f, 0.f);
	directionalLight->setPosition(50.f, 50.f, 50.f);
	directionalLight->generateViewMatrix();
	directionalLight->generateOrthoMatrix((float)sceneWidth, (float)sceneHeight, 2.f, 100.f);


	//Default Pointlight Light Values
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
	pointlight[1]->setDiffuseColour(1.0f, 0.0f,0.0f, 1.0f);
	pointlight[1]->setPosition(50.0f, 10.0f, 50.0f);
	pointlight[1]->setDirection(1.f, 1.f, 1.0f);
	pointlight[1]->generateProjectionMatrix(2.f, 100.f);
	//Default Attenuation Factors
	pointlight[1]->setAttenuationFactors(XMFLOAT3(1.f, 0.175f, 0.0f));

	#pragma endregion
	
	//Depth Map initialization
	#pragma region Depthmaps

	//Variables for defining shadow map parameters
	int shadowmapWidth = 2048;
	int shadowmapHeight = 2048;

	//Initialize Directional Shadowmap.
	depthmapDirectional = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	//Initialize the Camera depth map.
	cameraDepthMap = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);

	//Initialize ALL Shadowmaps of Pointlights
	for (size_t i = 0; i < numberOfPointlights * 6; i++)
	{
		pointlightShadows[i] = new ShadowMap(renderer->getDevice(), shadowmapWidth, shadowmapHeight);
	}

	#pragma endregion

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
		heightmap = textureMgr->getTexture(L"CliftHeight");
		break;

	case 2:
		heightmap = textureMgr->getTexture(L"CoastHeight");
		break;
	case 3:
		heightmap = textureMgr->getTexture(L"LakeHeight");
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
		texture = textureMgr->getTexture(L"CliftTexture");
		break;
	case 2:
		texture = textureMgr->getTexture(L"CoastTexture");
		break;
	case 3:
		texture = textureMgr->getTexture(L"LakeTexture");
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

	//Render Grass with Geometry Cull turned Off
	renderer->setNoCullMode(true);
	grassMesh->sendData(renderer->getDeviceContext(), D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
	grassShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, camViewMatrix, camProjectionMatrix, textureMgr->getTexture(L"WindMap"), getTerrainHeigthmap(),
		textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude, directionalLight, depthmapDirectional->getDepthMapSRV());

	grassShader->setPixelShaderParameters(renderer->getDeviceContext(), bottomGrassColor, topGrassColor);
	grassShader->setHullshaderParameters(renderer->getDeviceContext(), grassDensity);
	grassShader->setGeometryShaderParameters(renderer->getDeviceContext(), grassMaxHeight, grassWidth, windStrength, windFrequency, time, grassSpawnThreshold);
	grassShader->render(renderer->getDeviceContext(), grassMesh->getIndexCount());
	renderer->setNoCullMode(false);

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

	// Set the render target to be the render to texture and clear it
	renderTexture->setRenderTarget(renderer->getDeviceContext());
	renderTexture->clearRenderTarget(renderer->getDeviceContext(), 0.258, 0.835, 0.843, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();


	//Toggle wiregrame mode only for this portion
	renderer->setWireframeMode(wireframe);

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	//Render Terrain Plane
	if (renderPlane)
	{

		// Send geometry data, set shader parameters, render object with shader
		planeMesh->sendData(renderer->getDeviceContext());
		PlaneShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, getTerrainTexture(), camera->getPosition(),
		amplitude, getTerrainHeigthmap(), directionalLight, pointlight, depthmapDirectional->getDepthMapSRV(), pointlightDepthTextures,pointlightView,textureTiling);
		PlaneShader->setHullShaderParameters(renderer->getDeviceContext(), terrainTessellationFactor, terrainDynamicTessellationFactor,
			terrainDynamicTessellationToggle, terrainDystanceScalar);
		PlaneShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());
	}

	//Render Grass Plane
	if (renderGrass)
	{
		renderer->setNoCullMode(true);
		grassMesh->sendData(renderer->getDeviceContext(), D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
		grassShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"WindMap"), getTerrainHeigthmap(),
			textureMgr->getTexture(L"Noise"), textureMgr->getTexture(L"GrassSpawn"), amplitude, directionalLight, depthmapDirectional->getDepthMapSRV());

		grassShader->setPixelShaderParameters(renderer->getDeviceContext(), bottomGrassColor, topGrassColor);
		grassShader->setHullshaderParameters(renderer->getDeviceContext(), grassDensity);
		grassShader->setGeometryShaderParameters(renderer->getDeviceContext(), grassMaxHeight, grassWidth, windStrength, windFrequency, time,grassSpawnThreshold);


		grassShader->render(renderer->getDeviceContext(), grassMesh->getIndexCount());
		renderer->setNoCullMode(false);
	}

	//Render Water Plane
	if (renderWater)
	{
		XMMATRIX waterWorldMatrix = worldMatrix * XMMatrixTranslation(0.0f, Sealevel, 0.0f);
		waterPlaneMesh->sendData(renderer->getDeviceContext());
		renderer->setAlphaBlending(1);
		WaterShader->setShaderParameters(renderer->getDeviceContext(), waterWorldMatrix, viewMatrix, projectionMatrix, camera->getPosition(),
		WaveSettings, WaveDirection, time);
		WaterShader->setPixelShaderParameters(renderer->getDeviceContext(), waterOffset, depthScalar, Sealevel, amplitude, deepColor,shallowColor, getTerrainHeigthmap());
		WaterShader->setHullShaderParameters(renderer->getDeviceContext(), tessellationFactor, dynamicTessellationFactor,
			dynamicTessellationToggle, distanceScalar);
		WaterShader->setLightingShaderParameters(renderer->getDeviceContext(), directionalLight, pointlight, depthmapDirectional->getDepthMapSRV(), pointlightDepthTextures, pointlightView,lightingWater);


		WaterShader->render(renderer->getDeviceContext(), waterPlaneMesh->getIndexCount());
		renderer->setAlphaBlending(0);
	}

	//Render Sphere to demonstrate Shadows.
	XMMATRIX cubeWorldMatrix = worldMatrix * XMMatrixTranslation(ballposition[0], ballposition[1], ballposition[2]);
	CubeShadow->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), cubeWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	textureShader->render(renderer->getDeviceContext(), CubeShadow->getIndexCount());

	//Render Pointlight 1 Gyzmos.
	XMMATRIX pointlightMatrix = worldMatrix * XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixTranslation(pointlight[0]->getPosition().x , pointlight[0]->getPosition().y, pointlight[0]->getPosition().z);
	pointlightGyzmos1->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), pointlightMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	textureShader->render(renderer->getDeviceContext(), pointlightGyzmos1->getIndexCount());

	//Render Pointlight 2 Gyzmos.
	XMMATRIX pointlightMatrix2 = worldMatrix * XMMatrixScaling(0.5f, 0.5f, 0.5f) * XMMatrixTranslation(pointlight[1]->getPosition().x, pointlight[1]->getPosition().y, pointlight[1]->getPosition().z);
	pointlightGyzmos2->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), pointlightMatrix2, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"));
	textureShader->render(renderer->getDeviceContext(), pointlightGyzmos2->getIndexCount());


	//Set it always to walse so it doens't get beyond this point and wareframe render textures
	renderer->setWireframeMode(false);
	// Swap the buffers
	renderer->setBackBufferRenderTarget();

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

	depthOfFieldTexture->setRenderTarget(renderer->getDeviceContext());
	depthOfFieldTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	//Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	orthoMatrix = depthOfFieldTexture->getOrthoMatrix();

	//Render for Vertical Blur
	renderer->setZBuffer(false);
	downSampleOrthoMesh->sendData(renderer->getDeviceContext());
	depthFieldShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, downSampleTexture->getShaderResourceView(),
		verticalBlurredSceneTexture->getShaderResourceView(),cameraDepthMap->getDepthMapSRV(),DepthFieldSettings);
	depthFieldShader->render(renderer->getDeviceContext(), downSampleOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::upSampleTexture()
{

	XMMATRIX worldMatrix, baseViewMatrix, orthoMatrix;

	upsampleTexture->setRenderTarget(renderer->getDeviceContext());
	upsampleTexture->clearRenderTarget(renderer->getDeviceContext(), 1.0f, 1.0f, 1.0f, 1.0f);

	worldMatrix = renderer->getWorldMatrix();
	baseViewMatrix = camera->getOrthoViewMatrix();
	//Get the full resolution ortho matrix from the render to texture.
	orthoMatrix = upsampleTexture->getOrthoMatrix();

	//Render for Vertical Blur
	renderer->setZBuffer(false);
	orthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, depthOfFieldTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), orthoMesh->getIndexCount());
	renderer->setZBuffer(true);
	
	//Reset the render target back to the original back buffer and not the render to texture anymore.
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

	//Main Menu Bar Start
	ImGui::BeginMainMenuBar();
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Text("Time elapsed: %.2f", time);
	ImGui::Text("Camera Position: X: %.2f Y: %.2f Z: %.2f", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	ImGui::EndMainMenuBar();
	//End Menu Bar


	//Start Main UI
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
		//Toggles lighting on water on and off
		ImGui::Checkbox("Lighting affects water", &lightingWater);
		//Move the plane up or down
		ImGui::SliderFloat("Water Level", &Sealevel, -20.0f, 20.0f);
		

		//Header for the settings of Wave 1
		if(ImGui::CollapsingHeader("Wave 1 Settings"))
		{
			ImGui::SliderFloat("Wave Amplitude", &WaveSettings[0].y, 0.1f, 2.0f);
			ImGui::SliderFloat("Wave Frequency: ", &WaveSettings[0].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave Speed: ", &WaveSettings[0].w, 1.0f, 20.0f);
			//Smootheness
		//Direction Vector
			ImGui::SliderAngle("Wave Direction: ", &WaveDirection[0], 0.0f, 180.0f);
			ImGui::SliderFloat("Wave Smoothness: ", &WaveSettings[0].x, 0.0f, 1.0f);
		}
		ImGui::Separator();

		//Header for the settings of Wave 2
		if (ImGui::CollapsingHeader("Wave 2 Settings"))
		{
			ImGui::SliderFloat("Wave 2 Amplitude", &WaveSettings[1].y, 0.1f, 2.0f);
			ImGui::SliderFloat("Wave 2 Frequency: ", &WaveSettings[1].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 2 Speed: ", &WaveSettings[1].w, 1.0f, 20.0f);
			//Smootheness
			//Direction Vector
			ImGui::SliderAngle("Wave 2 Direction: ", &WaveDirection[1], 0.0f, 180.0f);
			ImGui::SliderFloat("Wave 2 Smoothness: ", &WaveSettings[1].x, 0.0f, 1.0f);
			
		}
		ImGui::Separator();

		//Header for the settings of Wave 3
		if (ImGui::CollapsingHeader("Wave 3 Settings"))
		{
			
			ImGui::SliderFloat("Wave 3 Amplitude", &WaveSettings[2].y, 0.1f, 2.0f);
			ImGui::SliderFloat("Wave 3 Frequency: ", &WaveSettings[2].z, 1.0f, 20.0f);
			ImGui::SliderFloat("Wave 3 Speed: ", &WaveSettings[2].w, 1.0f, 20.0f);
			//Smootheness
			//Direction Vector
			ImGui::SliderAngle("Wave 3 Direction: ", &WaveDirection[2], 0.0f, 180.0f);
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
				ImGui::SliderFloat("Distance Scalar", &distanceScalar, 1, 150);
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

		static const char* selectedItem = heightmapsLabel[selectedHeightmap];
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

		static const char* selectedItemT = textureLabel[selectedTexture];
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
		ImGui::SliderFloat("Amplitude Heightmap", &amplitude, 1.0f, 100.0f);

		ImGui::SliderFloat("Tiling Factor", &textureTiling, 1.0f, 25.0f);

		//Header for the settings of water tessellation
		if (ImGui::CollapsingHeader("Terrain Tessellation"))
		{
			ImGui::Checkbox("Dynamic Tessellation##1", &terrainDynamicTessellationToggle);
			if (terrainDynamicTessellationToggle)
			{
				ImGui::SliderFloat("Dynamic Factor##1", &terrainDynamicTessellationFactor, 0, 15);
				ImGui::SliderFloat("Distance Scalar##1", &terrainDystanceScalar, 1, 150);
			}
			else
				ImGui::SliderFloat("Tessellation Factor##1", &terrainTessellationFactor, 0, 25);

			//ImGui::SliderFloat("Tessellation Factor", &TesellationFactor.x, 1.0f, 25.0f);

		}

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

		ImGui::Checkbox("Lighting affects water", &lightingWater); ImGui::SameLine(); ImGuiFunctions::ExclamationmarkTooltip("If this is active and waves have different directions when all of their amplitudes are bellow 1 it might create non desired results.");
		ImGui::ColorEdit4("Ambient Light Color", ambientLight, ImGuiColorEditFlags_NoInputs);
		ImGui::Checkbox("Directional Light", &dirlight);
		directionalLight->setAmbientColour(ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3]);

		if (!dirlight)
		{
			directionalLight->setDiffuseColour(0, 0, 0, 1.f);
			directionalLight->setSpecularColour(0,0,0,1.f);
			directionalLight->setSpecularPower(0);
		}
		else
		{
			directionalLight->setDiffuseColour(directionalDiffuse[0], directionalDiffuse[1], directionalDiffuse[2], 1.f);
			directionalLight->setSpecularColour(specularColor[0], specularColor[1], specularColor[2], specularColor[3]);
			directionalLight->setSpecularPower(specularPower);
		}

		if (ImGui::CollapsingHeader("Directional Light Settings"))
		{
			//Lighting bool window
			ImGui::ColorEdit4("Directional Diffuse Color", directionalDiffuse, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");

			//If its on set it if it isn't don't

			directionalLight->setDirection(direction[0], direction[1], direction[2]);

			ImGui::ColorEdit4("Specular Color", specularColor, ImGuiColorEditFlags_NoInputs);
			ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");
			ImGui::SliderFloat("Specular Power", &specularPower, 1, 20);

			//This is temporal, will be changed to SliderAngle and calculate vectors on Shader from the angle inputed
			ImGui::SliderFloat3("Directional Light Direction:", direction, -1.f, 1.f);
			if (direction[0] == 0.0f)
				direction[0] = 0.000001;
			if (direction[1] == 0.0f)
				direction[1] = 0.000001;
			if (direction[2] == 0.0f)
				direction[2] = 0.000001;
			

			ImGui::SliderFloat3("Directional Light Position:", position, -50.f, 50.f);
			directionalLight->setPosition(position[0], position[1], position[2]);
		
		}
		


		ImGui::Separator();
		

		
		if (ImGui::CollapsingHeader("Pointlight Settings"))
		{
			ImGui::SliderFloat3("Pointlight 1 Position:", pointPosition, 0.f, 120.f);
			pointlight[0]->setPosition(pointPosition[0], pointPosition[1], pointPosition[2]);

			ImGui::ColorEdit4("Pointlight Diffuse", pointlightDiffuse, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			pointlight[0]->setDiffuseColour(pointlightDiffuse[0], pointlightDiffuse[1], pointlightDiffuse[2], 1.f);


			ImGui::SameLine(); ImGui::Text("Pointlight Diffuse Color Picker");
			ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");

			ImGui::SliderFloat3("Pointlight Attenuation", pointlightAtt, 0.f, 1.f);

			ImGui::SliderFloat3("Pointlight 2 Position:", pointPosition2, 0.f, 120.f);
			pointlight[1]->setPosition(pointPosition2[0], pointPosition2[1], pointPosition2[2]);

			ImGui::ColorEdit4("Pointlight 2 Diffuse", pointlightDiffuse2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			pointlight[1]->setDiffuseColour(pointlightDiffuse2[0], pointlightDiffuse2[1], pointlightDiffuse2[2], 1.f);


			ImGui::SameLine(); ImGui::Text("Pointlight Diffuse Color Picker");
			ImGui::SameLine(); ImGuiFunctions::QuestionmarkTooltip("Click on box to pop up picker.");

			ImGui::SliderFloat3("Pointlight 2 Attenuation", pointlightAtt2, 0.f, 1.f);

			

			pointlight[0]->setAttenuationFactors(XMFLOAT3(pointlightAtt[0], pointlightAtt[1], pointlightAtt[2]));
			pointlight[1]->setAttenuationFactors(XMFLOAT3(pointlightAtt2[0], pointlightAtt2[1], pointlightAtt2[2]));
		}
		
		ImGui::SliderFloat3("Sphere position:", ballposition, 0.f, 120.f);

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

	//Grass bool window
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
		ImGui::SameLine();
		ImGuiFunctions::QuestionmarkTooltip("Changes the tessellation of the place thus increasing the number of vertex where to spawn grass.");
		ImGui::SliderFloat("Grass Max Height", &grassMaxHeight, 1, 4);
		ImGui::SliderFloat("Grass Width", &grassWidth, 0.2f, 5);
		ImGui::SliderFloat("Wind Strength", &windStrength, 1, 3);
		ImGui::SliderFloat("Wind Frequency", &windFrequency, 0.f, 0.2f);
		ImGui::SliderFloat("Grass Spawn Threshold", &grassSpawnThreshold, 0.f, 1.f); 
		ImGui::SameLine();
		ImGuiFunctions::QuestionmarkTooltip("The number that will be compared against the sampled noise texture in the shader. Higher value is more grass.");

		ImGui::End();

	}

	ImGui::End();
	//End Main UI

	//Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

