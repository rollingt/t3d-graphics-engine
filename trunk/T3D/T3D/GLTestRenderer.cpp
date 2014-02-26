// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GLTestRenderer.cpp
//
// A dummy renderer that ignores the scene entirely.  Intended to be used as an OpenGL snadbox.

#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>

#include "GLTestRenderer.h"

namespace T3D{

	GLTestRenderer::GLTestRenderer(void)
	{
	}


	GLTestRenderer::~GLTestRenderer(void)
	{
	}

	
	void GLTestRenderer::render(Transform *root){
		// Add random OpenGL code here :)
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
			glColor4f(1.0, 0.0, 0, 1.0);
			glVertex2f(-0.5,-0.5);
			glVertex2f(0.5,-0.5);
			glVertex2f(0.0,0.5);
		glEnd();
	}

}
