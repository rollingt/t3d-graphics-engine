// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// ShaderTest.cpp
//
// A simple application used for testing lighting shaders
#pragma once

#include "WinGLApplication.h"

namespace T3D{

	//! \brief For testing OpenGL Lighting shaders.
	class ShaderTest :
		public WinGLApplication
	{
	public:
		ShaderTest(void);
		~ShaderTest(void);
	
		bool init();
	};

}

