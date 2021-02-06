// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// t3dtest.h
//
// Example t3dapplication
#pragma once

#include "WinGLApplication.h"

namespace T3D
{

	class T3DTest :
		public WinGLApplication
	{
	public:
		T3DTest(void)  = default;
		~T3DTest(void) = default;

		bool init();
	};

}
