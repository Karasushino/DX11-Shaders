// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframeworkw
#include "HeightmapShader.h"
#include "TessellationShader.h"
#include "QuadPlaneMesh.h"


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

private:
	TessellationMesh* mesh;
	HeightmapShader* PlaneShader;
	TessellationShader* WaterShader;
	XMFLOAT4 EdgeTesellation;
	XMFLOAT2 InsideTesellation;
	float amplitude;
	float Sealevel;

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

};

#endif