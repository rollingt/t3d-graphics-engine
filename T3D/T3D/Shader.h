// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Shader.h
//
// Abstract bass class for shaders

#pragma once

#include <string>

namespace T3D {

	//! Base class for Shaders.
	class Shader
	{
	public:
		//! \brief Create renderer-friendly Shader source code from Vertex and Fragment sources.
		Shader(std::string vertFilename, std::string fragFilename);
		
		//! \brief Destroy shader (trivially);
		virtual ~Shader(void) = default;
		
		virtual void compileShader() = 0;
		virtual void bindShader()    = 0;
		virtual void unbindShader()  = 0;


	protected:
		std::string vertSource, fragSource;
	};

}

