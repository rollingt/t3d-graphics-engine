// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GLShader.h
//
// Class for creating and compiling a GLSL shader

#pragma once

#include "Shader.h"

namespace T3D {

	//! \brief OpenGL Shader subclass for creating and compiling shaders from source code.
	class GLShader : public Shader
	{
	public:
		//! \brief Create GL shader program using Vertex and Fragment source code.
		//! \note Check `T3D_Log.txt` if your shader program is not working!
		GLShader(std::string vertFilename, 
				 std::string fragFilename)  : Shader(vertFilename, fragFilename),
											  vertID(0),
		      								  fragID(0),
		      								  id    (0) { }

		~GLShader(void) = default;
		
		virtual void compileShader();
		virtual void bindShader();
		virtual void unbindShader();

	protected:
		uint32_t vertID;
		uint32_t fragID;
		uint32_t id;

	private:
		void checkShaderErrors(uint32_t shaderID);
		void checkProgramErrors(uint32_t programID);
	};

}

