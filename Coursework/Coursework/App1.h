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


class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();
	void depthPass();
	void finalPass();
	

private:
	TessellationMesh* mesh;
	HeightmapShader* PlaneShader;
	TessellationShader* WaterShader;
	DepthShaderHeightmap* DepthHeightmapShader;
	DepthShader* depthShader;
	GeometryShader* grassShader;

	ShadowMap* depthmapDirectional;


	TextureShader* textureShader;



	XMFLOAT4 EdgeTesellation;
	XMFLOAT2 InsideTesellation;
	float amplitude;
	float Sealevel;

	float position[3];

	Light* light[3];


	// x = Peakness;
	//y = amplitude;
	//z =  frequency;
	//w = speed;
	XMFLOAT4 WaveSettings[3];

	//Angle
	float WaveDirection[3] = { 0.f };

	//Time passed
	float time = 0.f;

	float direction[3] = { 0.f };
	float diff[3] = { 0.f };

	QuadPlaneMesh* planeMesh;
	QuadPlaneMesh* waterPlaneMesh;
	PlaneMesh* grassMesh;
	SphereMesh* CubeShadow;
	OrthoMesh* smolOrthoMesh;

};

#endif