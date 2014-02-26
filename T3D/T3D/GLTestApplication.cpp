// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GLTestApplication.cpp
//
// A dummy application for running the GLTestRenderer (used as an OpenGL sandbox)

#include "GLTestApplication.h"
#include "GLTestRenderer.h"

namespace T3D{

	GLTestApplication::GLTestApplication(void)
	{
		surf = NULL;
		running = false;
		renderer = new GLTestRenderer();		
		root = new Transform(NULL,"Root");
	}


	GLTestApplication::~GLTestApplication(void)
	{
	}

	
	bool GLTestApplication::init(){
		WinGLApplication::init();
		
		return true;
	}

}
