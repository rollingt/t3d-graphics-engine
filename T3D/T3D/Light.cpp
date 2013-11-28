// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// light.cpp
//
// Compnent to add lights to a game object

#include "Light.h"

namespace T3D
{

	Light::Light(int type)
	{
		this->type = type;
		gameObject = 0;
		enabled = true;
	}


	Light::~Light(void)
	{
	}

}