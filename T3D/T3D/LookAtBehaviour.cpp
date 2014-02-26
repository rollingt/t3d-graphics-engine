// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// LookAtBehaviour.cpp
//
// A component used for making a component face another transform.  Basically just a wrapper for the Transform lookAt method.

#include "LookAtBehaviour.h"
#include "GameObject.h"

namespace T3D
{
	
	LookAtBehaviour::~LookAtBehaviour(void)
	{
	}

	void LookAtBehaviour::update(float dt){
		gameObject->getTransform()->lookAt(target->getWorldPosition());
	}

}
