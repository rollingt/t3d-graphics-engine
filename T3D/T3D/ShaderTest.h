#pragma once
#include "winglapplication.h"

namespace T3D{

	class ShaderTest :
		public WinGLApplication
	{
	public:
		ShaderTest(void);
		~ShaderTest(void);
	
		bool init();
	};

}

