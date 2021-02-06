// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// RotateBehaviour.h
//
// Simple behaviour to rotate an object
#pragma once

#include "Component.h"
#include "Vector3.h"

namespace T3D
{

	class RotateBehaviour :
		public Component
	{
	public:
		RotateBehaviour(Vector3 r) : rotation(r) { }
		~RotateBehaviour(void) = default;
		
		virtual void update(float dt);
	protected:
		Vector3 rotation;
	};

}
