// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GLShader.cpp
//
// Class for creating and compiling a GLSL shader

#include "GLShader.h"
#include <gl/glew.h>
#include <gl/GL.h>

#include "Logger.h"

namespace T3D {

	void GLShader::compileShader()
	{
		vertID = glCreateShader(GL_VERTEX_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		/* Grab strings and lengths. */
		GLchar const *vert       = vertSource.c_str();
		GLint  const  vertLength = vertSource.size();
		GLchar const *frag       = fragSource.c_str();
		GLint  const  fragLength = fragSource.size();

		logger::Log(priority::Tracing,
					output_stream::All,
					category::Video,
					"Compiling Shader...\nVertex Source :\n```\n%s\n```\nFragment Source :\n```\n%s\n```"
					,
					vert,
					frag);
		
		/* Give the shader compiler our vertex and fragment sources, compile them, and check for errors */
		glShaderSource(vertID, 1, &vert, &vertLength);
		glShaderSource(fragID, 1, &frag, &fragLength);

		glCompileShader(vertID);
		checkShaderErrors(vertID);

		glCompileShader(fragID);
		checkShaderErrors(fragID);

		id = glCreateProgram();

		glAttachShader(id, vertID);
		glAttachShader(id, fragID);

		glLinkProgram(id);
		checkProgramErrors(id);
	}

	/* Helper functions for printing diagnostic messages at different stages of shader and program
	   compilation and linkage.
	   Note that the nomenclature for GL shaders isn't great. Also, these could be folded into a 
	   small inline function or macro pretty easily, but are left as is for explicitness. */
	void GLShader::checkProgramErrors(uint32_t programID)
	{
		GLint result;
		GLchar *log;

		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		if (result != GL_TRUE)
		{
			GLint length;
			glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &length);
			log = (GLchar*)malloc(length);
			glGetProgramInfoLog(programID, length, NULL, log);

			logger::Log(priority::Error,
						output_stream::All,
						category::Video,
						"Shader program did not link! ID :: %u\nReason: %s"
						,
						programID,
						log);

			free(log);
		}
		else
		{
			logger::Log(priority::Info,
						output_stream::All,
						category::Video,
						"Shader program compiled successfully! ID :: %u"
						,
						programID);
			
		}
	}


	void GLShader::checkShaderErrors(uint32_t shaderID)
	{
		GLint result;
		GLchar *log;

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE)
		{
			GLint length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			log = (GLchar *) malloc(length);
			glGetShaderInfoLog(shaderID, length, NULL, log);

			logger::Log(priority::Error,
						output_stream::All,
						category::Video,
						"Shader did not compile! ID :: %u\nReason: %s"
						,
						shaderID,
						log);

			free(log);
		}
		else
		{
			logger::Log(priority::Info,
						output_stream::All,
						category::Video,
						"Shader compiled successfully! ID :: %u"
						,
						shaderID);
		}
	}

	void GLShader::bindShader(){
		glUseProgram(id);
	}
	
	void GLShader::unbindShader(){
		glUseProgram(0);
	}

}
