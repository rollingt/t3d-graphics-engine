// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// component.cpp
//
// Abstract component class for game objects
// Used to add behaviours and other functionality to game objects
// Automatically updated by application

#include "Component.h"
#include "GameObject.h"

namespace T3D
{
	Component::Component(void)
	{
		gameObject = NULL;
	}


	Component::~Component(void)
	{
	}
}
