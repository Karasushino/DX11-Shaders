// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframeworkw
#include "HeightmapShader.h"
#include "TessellationShader.h"
#include "QuadPlaneMesh.h"
#include "DepthShaderHeightmap.h"
#include "DepthShader.h"
#include "TextureShader.h"
#include "GeometryShader.h"
#include "GeometryShaderDepth.h"
#include "LightedTextureShader.h"

#include "HorizontalBlurShader.h"
#include "VerticalBlurShader.h"

#include "DepthOfFieldShader.h"
#include "ImGuiFunctions.h"


class App1 : public BaseApplication
{
public:

	struct WaterBufferType
	{
		float heightmapAmplitude;
		float waterPlaneHeight;
		float offsett;
		float depthScalar;
	};

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);
	void style();

	bool frame();

protected:
	//Main Render function
	bool render();

	//HUD 
	void gui();

	//Depthpasses
	void depthPass();
	//Gets depth map of camera
	void cameraDepthPass();
	//Creates the depthmaps of the pointlights 
	void pointlightDepthPass();


	
	//Render scene to a RenderTexture for Post processing
	void firstPass();


	//Downsample
	void downsample();

	//Blur scene (for DOP)
	void horizontalBlur();
	void verticalBlur();
	//Do DOP calculations.
	void depthOfFieldPass();

	//Upsample
	void upSampleTexture();

	//Render the scene that will be shown to player
	void finalPass();
	
	//Helper Functions

	//Returns the terrain heightmap based on the selected one
	ID3D11ShaderResourceView* getTerrainHeigthmap();
	
	ID3D11ShaderResourceView* getTerrainTexture();


private:
	//Region of Shaders
	#pragma region Shaders 

	//Tesellated Shaders 
	TessellationMesh* mesh;
	TessellationShader* WaterShader;
	HeightmapShader* PlaneShader;

	//Geometry Shaders
	GeometryShader* grassShader;
	GeometryShaderDepth* grassShaderDepth;

	//Non Tesellated Shaders
	DepthShaderHeightmap* DepthHeightmapShader; //Shader to only render for depth map generation
	LightedTextureShader* cubeShader; 

	//Post Processing
	HorizontalBlurShader* horizontalBlurShader; //Gausian blur horizontal
	VerticalBlurShader* verticalBlurShader; //Gausian blur vertical
	DepthOfFieldShader* depthFieldShader; //Depth of field post processing

	//Depth Maps 
	DepthShader* depthShader;
	

	//Basic Texture shader.
	TextureShader* textureShader;

#pragma endregion


	//Position of sphere
	float ballposition[3] = { 50.0f, 15.f, 50.0f };




	//Amplitude of terrain, height of terrain. Scalar for heightmap data.
	float amplitude;

	//Render flags to render objects of the scene or not do so.
	bool renderGrass = true;
	bool renderWater = true;
	bool renderPlane = true;
	//Flag to do activate/deactivate post processing
	bool togglePostprocess = false;


	/*x = Peakness(How sharp the wave is (not amplitude))
	  y = amplitude
	  z = frequency
	  w = speed
	  */
	XMFLOAT4 WaveSettings[3];

	//Angle of wave (direction) (default must be in radiants)
	float WaveDirection[3] = { 2.0618f ,3.15f,1.13f };

	//Time passed
	float time = 0.f;

	
	//Settings for Water Color and Level
	float waterOffset = 0.0f;
	float depthScalar = 17.f;
	float Sealevel = 14.f;

	//Region of geometry declarations
	#pragma region Geometry

	//Planes and geometry of scene.
	QuadPlaneMesh* planeMesh;
	QuadPlaneMesh* waterPlaneMesh;
	PlaneMesh* grassMesh;
	SphereMesh* CubeShadow;

	#pragma endregion

	//Region of Orthomeshes
	#pragma region Orthomeshes

	//Debugging ortho mesh
	OrthoMesh* smolOrthoMesh;

	//Post Processing ortho meshes
	OrthoMesh* orthoMesh;
	OrthoMesh* downSampleOrthoMesh;

	#pragma endregion

	/**Post processing
	Render Textures for Post processing*/
	#pragma region RenderTextures
	RenderTexture* renderTexture;
	RenderTexture* horizontalBlurredSceneTexture;
	RenderTexture* verticalBlurredSceneTexture;

	RenderTexture* downSampleTexture;
	RenderTexture* upsampleTexture;
	RenderTexture* depthOfFieldTexture;

	#pragma endregion
	/*Settings for the depth of field
	x = focus distance
	y = focus range
	z = near plane
	w = far plane */
	XMFLOAT4 DepthFieldSettings;

	//Depth Maps
	//Orthogonal Depthmap
	ShadowMap* depthmapDirectional;
	//Depthmap of the camera
	ShadowMap* cameraDepthMap;

	

	//All Lighting Related
	#pragma region Lighting 
	const static int numberOfPointlights = 2;

	//Position of dir light
	float position[3] = {50.f,50.f,50.f};


	//Position of point light
	float pointPosition[3] = { 50.f,15.f,50.f };
	//Position of pointlight 2
	float pointPosition2[3] = { 50.f,15.f,50.f };
	//Light data and settings.
	Light* directionalLight;
	Light* pointlight[numberOfPointlights];

	//Light Directions
	float direction[3] = { 0.7f, -0.7f, 0.f };

	//Light color diffuse
	float directionalDiffuse[4] = { 1,1,1,1 };
	float pointlightDiffuse[4] = { 1,1,1,1 };
	float pointlightAtt[3] = { 1.f, 0.175f, 0.0f };
	float pointlightAtt2[3] = { 1.f, 0.175f, 0.0f };
	float pointlightDiffuse2[4] = { 1,0,0,1 };


	//Store the depth maps in array to pass to GPU shader 
	ID3D11ShaderResourceView* pointlightDepthTextures[6*numberOfPointlights];
	//Shadowmap objects for the pointlights
	ShadowMap* pointlightShadows[6*numberOfPointlights];
	//View Matrix of Pointlights
	XMMATRIX pointlightView[6 * numberOfPointlights];

	//Pointlight directions for depthmaping
	XMFLOAT3 directions[6] = {
		XMFLOAT3(0.f,1.f,0.f),    // Up
		XMFLOAT3(0.f,-1.f,0.f),// Down
		XMFLOAT3(1.f,0.f,0.f),    // Right
		XMFLOAT3(-1.f,0.f,0.f),    // Left
		XMFLOAT3(0.f,0.f,1.f),    // Fowards
		XMFLOAT3(0.f,0.f,-1.f)    // Backwards
	};

	#pragma endregion
	

	//Water tessellation factors
	float tessellationFactor = 5.f;
	float dynamicTessellationFactor = 3.f;
	bool dynamicTessellationToggle = false;
	float dystanceScalar = 100.f;


	//Terrain tessellation factors
	float terrainTessellationFactor = 5.f;
	float terrainDynamicTessellationFactor = 3.f;
	bool terrainDynamicTessellationToggle = false;
	float terrainDystanceScalar = 100.f;

	float deepColor[4] = { 0.13f, 0.13f, 0.8f, 0.6f };
	float shallowColor[4] = { 0.1f, 0.9f, 0.9f, 0.2f };

	float topGrassColor[4] = { 0.0f, .3f, 0.f, 1.f };
	float bottomGrassColor[4] = { 0.0f, 1.0f, 0.f,1.f };

	float ambientLight[4] = { 0.35f, 0.35f, 0.35f, 1.0f };

	float grassDensity = 8.f;

	//Grass settings
	float grassMaxHeight = 2.f;
	float grassWidth = 0.5f;
	float windStrength = 1.5f;
	float windFrequency = 0.05f;
	float grassSpawnThreshold = 0.7f;

	bool wireframe = false;

	float textureTiling = 1.f;
	
	const char* heightmapsLabel[4] = { "Heightmap 1", "Clift","Coast","Lakes" };
	int selectedHeightmap = 3;

	const char* textureLabel[4] = { "Moss", "Clift", "Coast","Lakes" };
	int selectedTexture = 3;

	bool lightingWater = true;

	float specularPower = 10.f; 
	float specularColor[4] = { 1.f,1.f,1.f,1.f };


	HeightmapShader::CameraBufferType a;
};

#endif