// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	//Include DXframework

//All of my header files 
#pragma region My Class Headers

#include "HeightmapShader.h" //Include Terrain Shader Class
#include "WaterWavesShader.h" //Include Water Shader Class
#include "QuadPlaneMesh.h" //Include Plane made from Quads ready for tessellation.
#include "DepthShaderHeightmap.h" //Include Optimized Shader for Terrain Depth Passes.
#include "DepthShader.h" //Include Basic Depth Shader.
#include "TextureShader.h" //Include Basic Texture Shader.
#include "GrassShader.h" //Include Grass shader.
#include "GrassShaderDepth.h" //Include the Optimized Grass Shader for Depth Passes.
#include "HorizontalBlurShader.h" //Include the Horizontal Blur Shader for Postprocessing.
#include "VerticalBlurShader.h" //Include the Vertical Blur Shader for Postprocessing.
#include "DepthOfFieldShader.h" //Include the Depth of Field Shader for Postprocessing.
#include "ImGuiFunctions.h" //Include header file with Helper Functions to speed up ImGui usage. 

#pragma endregion

class App1 : public BaseApplication
{
public:

	App1();
	~App1();

	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	//Call to set ImGui style from Github.
	void style();

	bool frame();

protected:
	//Main Render Function
	bool render();

	//Main ImGui Function.
	void gui();

	//Depthpasses
	void depthPass();

	//Gets depth map of camera
	void cameraDepthPass();

	//Creates the depthmaps of the pointlights 
	void pointlightDepthPass();

	//Render scene to a RenderTexture for Post processing
	void firstPass();

	//Post Processing Functions Declarations
	#pragma region Post Processing Functions

	//Downsample the main Render Texture.
	void downsample();

	//Blur scene (for DOP)
	//Perform Horizontal Blur for Postprocessing.
	void horizontalBlur();
	//Perform Vertical Blur for Postprocessing.
	void verticalBlur();

	//Do Depth of Field calculations.
	void depthOfFieldPass();

	//Upsample the main Render Texture.
	void upSampleTexture();

	#pragma endregion

	//Render the scene that will be shown to User.
	void finalPass();
	
	//Helper Functions
	//Returns the Terrain Heightmap based on the selected state.
	ID3D11ShaderResourceView* getTerrainHeigthmap(); 
	//Returns the Terrain Texture based on the selected state.
	ID3D11ShaderResourceView* getTerrainTexture();


private:

	//Total Time Elpased in seconds (used for all the movement calculations in shaders).
	float time = 0.f;

	//Position of sphere to show the shadows working (ImGui).
	float ballposition[3] = { 50.0f, 15.f, 50.0f };

	//Render flags to render objects of the scene or not do so (ImGui).
	#pragma region Booleans

	bool renderGrass = true; //Toggle Rendering of Grass (ImGui).
	bool renderWater = true; //Toggle Rendering of Water (ImGui).
	bool renderPlane = true; //Toggle Rendering of Terrain (ImGui).
	bool lightingWater = true; //Toggle if Lighting Affects water ON and OFF (ImGui).
	bool togglePostprocess = false; //Flag to do activate/deactivate post processing (ImGui).
	bool wireframe = false; //Wireframe Toggle Boolean (ImGui).

	#pragma endregion

	//Region of Declarations Basic Shaders
	#pragma region Basic Shaders Declarations

	//Basic Depthmap Shader.
	DepthShader* depthShader;
	//Basic Texture Shader.
	TextureShader* textureShader;

	#pragma endregion

	//Water Declarations and Settings
	#pragma region Water Declarations Settings

	//Water Shader
	WaterWavesShader* WaterShader; //Shader for the Water Simulation.

	//Angle of wave (direction) (default must initialized in radiants) (ImGui).
	float WaveDirection[3] = { 2.0618f ,3.15f,1.13f };

	//Water Tessellation Parameters (ImGui)
	float tessellationFactor = 5.f; //Static Tessellation Factor of Water Shader (ImGui).
	float dynamicTessellationFactor = 3.f; //Dynamic Tessellation Factor of Water Shader (ImGui).
	bool dynamicTessellationToggle = false;//Toggle Dynamic Tessellation ON and OFF (ImGui).
	float distanceScalar = 100.f; //Dynamic Tessellation Distance Parameter of Water Shader, the distance needed between tessellation ranges. (ImGui).

	//Colors of the Water
	float deepColor[4] = { 0.13f, 0.13f, 0.8f, 0.6f }; //The Color to display at the deepest parts of the Water (ImGui).
	float shallowColor[4] = { 0.1f, 0.9f, 0.9f, 0.2f };//The Color to display at the shallowest parts of the Water (ImGui).

	/**Settings of the wave passed to the Shader @param x = Peak(How sharp the wave is (not amplitude))
	  @param y = amplitude @param z = frequency @param w = speed*/
	XMFLOAT4 WaveSettings[3];

	//Settings for Water Color and Level
	float waterOffset = 0.0f; //Offset to calculate the Depthness of the Water (ImGui).
	float depthScalar = 17.f; //Rate at which the water changes color based on Depth (ImGui).
	float Sealevel = 14.f; //Level at which the Water plane is at (ImGui).


	#pragma endregion
	
	//Terrain Declarations and Settings
	#pragma region Terrain 

	//Terrain Shaders
	HeightmapShader* PlaneShader; //Shader for Heightmap and Terrain rendering.
	DepthShaderHeightmap* DepthHeightmapShader; //Optimized Terrain Heightmap Shader for the Depth pass.

	//Amplitude of terrain, height of terrain. Scalar for heightmap data.
	float amplitude = 24.f;

	//Terrain Tessellation Parameters (ImGui)
	float terrainTessellationFactor = 5.f;	//Static Tessellation Factor of Terrain Shader (ImGui).
	float terrainDynamicTessellationFactor = 3.f;	//Dynamic Tessellation Factor of Terrain Shader (ImGui).
	bool terrainDynamicTessellationToggle = false;	//Toggle Dynamic Tessellation ON and OFF (ImGui).
	float terrainDystanceScalar = 100.f;	//Dynamic Tessellation Distance Parameter of Terrain Shader, the distance needed between tessellation ranges. (ImGui).

	//Texture Tiling of Heightmap texture. (ImGui).
	float textureTiling = 1.f;

	//Labels to Display for the Heightmap Picker in Terrain Settings (ImGui).
	const char* heightmapsLabel[4] = { "Provided Heightmap", "Clift","Coast","Lakes" };
	int selectedHeightmap = 3; //Integer that stores the selected map to then decide which heightmap to use for rendering.

	//Labels to Display for the Heightmap Picker in Terrain Texture Settings (ImGui).
	const char* textureLabel[4] = { "Moss", "Clift", "Coast","Lakes" };
	int selectedTexture = 3; //Integer that stores the selected map to then decide which heightmap to use for rendering.

	#pragma endregion

	//Grass Declarations and Settings
	#pragma region Grass

	//Geometry Grass Shaders
	GrassShader* grassShader; //Shader for Grass Generation.
	GrassShaderDepth* grassShaderDepth;  //Optimized Grass Shader for the Depth pass.

	//Colors of the Grass Blades
	float topGrassColor[4] = { 0.0f, .3f, 0.f, 1.f };	//The Color to display at the Highest Point of the Grass Blade (ImGui).
	float bottomGrassColor[4] = { 0.0f, 1.0f, 0.f,1.f };//The Color to display at the Lowest Point of the Grass Blade (ImGui).



	//Tessellation Factor of the Grass Plane, thus the Density of the Grass.
	float grassDensity = 8.f;

	//Grass Default Settings
	float grassMaxHeight = 2.f;	//Maximum Height of the Grass blade (Minimum is 1/3 of maximum). (ImGui).
	float grassWidth = 0.5f;	//Width of Grass Blade. (ImGui).
	float windStrength = 1.5f;	//Strength of Wind Blow. (ImGui).
	float windFrequency = 0.05f;//Frequency at which the DuDv texture gets sampled at. (ImGui).
	float grassSpawnThreshold = 0.7f;//Minimum value needed from the Sampled Noise Map to generate a Grass Blade.(ImGui).

	#pragma endregion

	//Region of Geometry Meshes Object declarations.
	#pragma region Geometry Meshes

	QuadPlaneMesh* planeMesh; //Terrain Plane Mesh.
	QuadPlaneMesh* waterPlaneMesh; //Water Plane Mesh.
	PlaneMesh* grassMesh; //Grass Plane Mesh.
	SphereMesh* CubeShadow; //Sphere Mesh to demonstrate shadows working. (It's funny because its a sphere but it's called Cube.)

	//Gyzmos Mesh of pointlights
	SphereMesh* pointlightGyzmos1; //Mesh of a Sphere to show where Pointlight 1 is in the world.
	SphereMesh* pointlightGyzmos2;//Mesh of a Sphere to show where Pointlight 2 is in the world.

	#pragma endregion

	//Region of Orthomeshes Declarations
	#pragma region Orthomeshes Declarations

	OrthoMesh* orthoMesh; //Full Resolution Orthomesh.
	OrthoMesh* downSampleOrthoMesh; //Downsampled Resolution Orthomesh.

	#pragma endregion

	//Post Processing Declarations and Settings
	#pragma region Post Processing

	//Post Processing Shaders
	HorizontalBlurShader* horizontalBlurShader; //Gausian blur horizontal Shader.
	VerticalBlurShader* verticalBlurShader; //Gausian blur vertical Shader.
	DepthOfFieldShader* depthFieldShader; //Depth of Field Post Processing Shader.

	//Depthmap of the Camera
	ShadowMap* cameraDepthMap;

	/*Settings for the depth of field @param x = focus distance @param y = focus range @param z = near plane
	@param w = far plane */
	XMFLOAT4 DepthFieldSettings;

		//Render Textures for Post processing
		#pragma region RenderTextures

		RenderTexture* renderTexture; //Main Render Texture of the Scene.
		RenderTexture* horizontalBlurredSceneTexture; //Render Texture with Horizontally blured Scene.
		RenderTexture* verticalBlurredSceneTexture; //Render Texture with Vertically blured Scene.

		RenderTexture* downSampleTexture; //Downsampled Render Texture for Postprocessing.
		RenderTexture* upsampleTexture; //Upsample Render Texture for Postprocessing.
		RenderTexture* depthOfFieldTexture; //Processed final Depth of Field Texture.

		#pragma endregion

	#pragma endregion

	//All Lighting Related (Including Depthmaps)
	#pragma region Lighting 
	
	//Super Important Parameter that defines the Number of Pointlights used in the scene. Need to change if more are added or removed. 
	const static int numberOfPointlights = 2;

		//Pointlight Declarations
		#pragma region Pointlights

		//Data Array for ALL the Pointlights of the scene.
		Light* pointlight[numberOfPointlights]; 

		//Positions of Pointlights
		float pointPosition[3] = { 50.f,15.f,50.f }; //Position of Pointlight 1 (ImGui).
		float pointPosition2[3] = { 50.f,15.f,50.f };//Position of Pointlight 2 (ImGui).

		//Light Color Diffuse Declarations
		float pointlightDiffuse[4] = { 1,1,1,1 }; //Diffuse Color of the Pointlight 1 (ImGui).
		float pointlightDiffuse2[4] = { 1,0,0,1 };//Diffuse Color of the Pointlight 2 (ImGui).
		float pointlightAtt[3] = { 1.f, 0.175f, 0.0f }; //Attenuation of the Pointlight 1 (ImGui).
		float pointlightAtt2[3] = { 1.f, 0.175f, 0.0f };//Attenuation of the Pointlight 2 (ImGui).
	
		//Depth Maps Related
		ID3D11ShaderResourceView* pointlightDepthTextures[6 * numberOfPointlights]; //Array that stores Resource Views of the Pointlight Depthmaps to easily pass to the GPU. 
		ShadowMap* pointlightShadows[6 * numberOfPointlights]; //Shadowmap objects for the pointlights
		XMMATRIX pointlightView[6 * numberOfPointlights]; //Array containing the View Matrix of Pointlights.

		//Pointlight Directions for depthmaping @param Up @param Down @param Right @param Left @param Foward @param Backward
		XMFLOAT3 directions[6] = {
			XMFLOAT3(0.f,1.f,0.f),		//Up
			XMFLOAT3(0.f,-1.f,0.f),		//Down
			XMFLOAT3(1.f,0.f,0.f),		//Right
			XMFLOAT3(-1.f,0.f,0.f),		//Left
			XMFLOAT3(0.f,0.f,1.f),		//Foward
			XMFLOAT3(0.f,0.f,-1.f)		//Backward
		};


		#pragma endregion

		//Directional Light Declarations
		#pragma region Directional Light

		//Light Settings.
		Light* directionalLight; //Data for the Directional Light of the scene.

		//Position of Directional Light. (Will change from where the Depth Map is rendered) (ImGui).
		float position[3] = {50.f,50.f,50.f};

		//Directional Light Direction.
		float direction[3] = { 0.7f, -0.7f, 0.f };

		//Diffuse Color of the Directional Light. (ImGui)
		float directionalDiffuse[4] = { 1,1,1,1 }; 

		//Ambient Light Parameter, changes Directional Light Ambient Parameter (ImGui).
		float ambientLight[4] = { 0.35f, 0.35f, 0.35f, 1.0f };

		//Specular Light Power of the Directional Light, ONLY affects WATER plane (ImGui).
		float specularPower = 10.f;

		//Specular Diffuse Color of the Directional Light, ONLY affects WATER plane (ImGui).
		float specularColor[4] = { 1.f,1.f,1.f,1.f };

		//Orthogonal Depthmap of Directional Light.
		ShadowMap* depthmapDirectional;

		#pragma endregion

	#pragma endregion
		
};

#endif