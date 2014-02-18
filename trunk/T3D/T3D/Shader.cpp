#include <iostream>
#include <fstream>
#include "Shader.h"

namespace T3D{

	Shader::Shader(std::string vertFilename, std::string fragFilename)
	{
		std::cout << "Loading shader source...\n";
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


	Shader::~Shader(void)
	{
	}

}
