// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// LookAtBehaviour.cpp
//
// A component used for making a component face another transform.  Basically just a wrapper for the Transform lookAt method.

#ifndef LOOKATBEHAVIOUR_H
#define LOOKATBEHAVIOUR_H

#include "component.h"
#include "Vector3.h"
#include "Transform.h"

namespace T3D
{
	class LookAtBehaviour :
		public Component
	{
	public:
		LookAtBehaviour(Transform *t) : target(t){};
		~LookAtBehaviour(void);
				
		virtual void update(float dt);

		Transform *target;
	};
}

#endif

