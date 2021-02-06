// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// RotateBehaviour.cpp
//
// Simple behaviour to rotate an object

#include "RotateBehaviour.h"
#include "GameObject.h"
#include "Transform.h"

namespace T3D
{
	void RotateBehaviour::update(float dt) {
		gameObject->getTransform()->rotate(rotation*dt);
	}

}
