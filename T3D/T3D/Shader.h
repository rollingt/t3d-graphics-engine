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

namespace T3D{

	class Shader
	{
	public:
		Shader(std::string vertFilename, std::string fragFilename);
		virtual ~Shader(void);
		
		virtual void compileShader() = 0;
		virtual void bindShader() = 0;
		virtual void unbindShader() = 0;

	protected:
		std::string vertSource, fragSource;
	};

}

