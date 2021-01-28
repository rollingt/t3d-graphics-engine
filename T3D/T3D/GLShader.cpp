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
#include <iostream>

namespace T3D{

	void GLShader::compileShader(){
		//std::cout << "Compiling shader...\n";
		//std::cout << vertSource << "\n\n";
		//std::cout << fragSource << "\n\n";

		vertID = glCreateShader(GL_VERTEX_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		GLchar const *vert = vertSource.c_str();
		GLint const vertLength = vertSource.size();
		GLchar const *frag = fragSource.c_str();
		GLint const fragLength = fragSource.size();
		
		GLint result;

		glShaderSource(vertID,1,&vert,&vertLength);
		glShaderSource(fragID,1,&frag,&fragLength);

		glCompileShader(vertID);
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &result);
		if (result!=GL_TRUE){
			std::cout << "Vertex program "<< vertID << " did not compile...\n";
			GLchar* log;
			GLint length;
			glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &length);
			log = (GLchar*)malloc(length);
			glGetShaderInfoLog(vertID,length,&length,log);
			std::cout<<log<<"\n";
		} else {
			//std::cout << "Vertex program "<< vertID << " compiled successfully\n";
		}
		glCompileShader(fragID);
		glGetShaderiv(fragID, GL_COMPILE_STATUS, &result);
		if (result!=GL_TRUE){
			std::cout << "Fragment program "<< fragID << " did not compile...\n";
		} else {
			//std::cout << "Fragment program "<< fragID << " compiled successfully\n";
		}

		//Check for compile errors (TODO)

		id = glCreateProgram();

		glAttachShader(id,vertID);
		glAttachShader(id,fragID);

		glLinkProgram(id);
		glGetShaderiv(id, GL_LINK_STATUS, &result);
		if (result!=GL_TRUE){
			std::cout << "Error linking shader...\n";
		} else {
			//std::cout << "Shader program "<< id << " linked successfully\n";
		}

		//Check for link errors (TODO)
	}

	void GLShader::bindShader(){
		glUseProgram(id);
	}
	
	void GLShader::unbindShader(){
		glUseProgram(0);
	}

}
