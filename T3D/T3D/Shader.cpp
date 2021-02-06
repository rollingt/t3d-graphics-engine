// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Shader.cpp
//
// Abstract bass class for shaders

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Logger.h"

namespace T3D {

	/*
	 * \param vertFileName Path to vertex shader source
	 * \param vertFileName Path to fragment shader source
	 *
	 * \note These are relative to T3D's starting directory - in Visual Studio, this will be from 'Debug'
	 * \note If you cannot load shader source code, check the console and log file for errors!
	 */
	Shader::Shader(std::string vertFilename, std::string fragFilename)
	{
		logger::Log(priority::Tracing,
					output_stream::File,
					category::Video,
					"Loading shader source...\n\t"
					"Vertex file: %s\n\t"
					"Fragment file: %s\n",
					vertFilename.c_str(),
					fragFilename.c_str());

		std::ifstream vertfile(vertFilename);
		std::ifstream fragfile(fragFilename);
		
		vertSource = "";
		while( vertfile.good() ) {
			std::string line;
			std::getline(vertfile, line);
			vertSource.append(line + "\n");
		}
		
		fragSource = "";
		while( fragfile.good() ) {
			std::string line;
			std::getline(fragfile, line);
			fragSource.append(line + "\n");
		}
	}

}
