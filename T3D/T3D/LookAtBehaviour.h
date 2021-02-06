// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// LookAtBehaviour.cpp
//
// A component used for making a component face another transform.  Basically just a wrapper for the Transform lookAt method.
#pragma once

#include "Component.h"
#include "Transform.h"

namespace T3D
{
	//! \brief A component that makes one Transform 'look at' another.
	class LookAtBehaviour :
		public Component
	{
	public:
		LookAtBehaviour(Transform *t) : target(t) { };
		~LookAtBehaviour(void) = default;
				
		virtual void update(float dt);

		Transform *target;
	};
}
