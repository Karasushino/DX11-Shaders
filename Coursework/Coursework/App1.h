// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframeworkw
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
	TessellationShader* PlaneShader;
	XMFLOAT4 EdgeTesellation;
	XMFLOAT2 InsideTesellation;
	float amplitude;


	Light* light[3];

	QuadPlaneMesh* planeMesh;
};

#endif