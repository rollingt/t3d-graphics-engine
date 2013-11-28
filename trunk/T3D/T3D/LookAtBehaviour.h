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

