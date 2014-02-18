#pragma once

#include "shader.h"

namespace T3D{

	class GLShader : public Shader
	{
	public:
		GLShader(std::string vertFilename, std::string fragFilename);
		~GLShader(void);
		
		virtual void compileShader();
		virtual void bindShader();
		virtual void unbindShader();
	protected:
		unsigned int vertID;
		unsigned int fragID;
		unsigned int id;
	};

}

