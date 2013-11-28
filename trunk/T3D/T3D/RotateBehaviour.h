#ifndef ROTATEBEHAVIOUR_H
#define ROTATEBEHAVIOUR_H

#include "component.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace T3D
{

	class RotateBehaviour :
		public Component
	{
	public:
		RotateBehaviour(Vector3);
		~RotateBehaviour(void);
		
		virtual void update(float dt);
	protected:
		Vector3 rotation;
	};

}

#endif
