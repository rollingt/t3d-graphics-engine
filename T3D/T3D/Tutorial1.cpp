// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Tutorial1.cpp
//
// Base application for tutorial 1.  Used in conjunction with DrawTask, a task for drawing onto a 2D texture.

#include "Tutorial1.h"
#include "WinGLApplication.h"
#include "GLRenderer.h"
#include "Camera.h"

namespace T3D 
{
	Tutorial1::Tutorial1(void)
	{
		drawTask = nullptr;
		drawArea = new Texture(renderer->WindowWidth, renderer->WindowHeight, false);
		drawArea->clear(Colour(255,255,255,255));
	}

	bool Tutorial1::init(){
		WinGLApplication::init();

		renderer->loadTexture(drawArea, false);
		renderer->add2DOverlay(drawArea,0,0);

		drawTask = new DrawTask(this,drawArea);
		addTask(drawTask);

		return true;
	}

}
