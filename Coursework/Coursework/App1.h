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


	// x = time;
	//y = amplitude;
	//z =  frequency;
	//w = speed;
	XMFLOAT4 WaveSettings;
	XMFLOAT3 WaveDirection;
	float direction[3] = { 0 };
	float smootheness = 1.0f;


	QuadPlaneMesh* planeMesh;
	QuadPlaneMesh* waterPlaneMesh;

};

#endif