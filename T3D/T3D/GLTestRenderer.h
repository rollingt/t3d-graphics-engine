// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GLTestRenderer.cpp
//
// A dummy renderer that ignores the scene entirely.  Intended to be used as an OpenGL snadbox.

#pragma once
#include "GLRenderer.h"

namespace T3D{

	class GLTestRenderer :
		public GLRenderer
	{
	public:
		GLTestRenderer(void);
		~GLTestRenderer(void);

		virtual void render(Transform *root);
	};

}

