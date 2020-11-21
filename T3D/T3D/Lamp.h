#pragma once
#include "GameObject.h"

namespace T3D {
	class Lamp : public GameObject
	{
	public:
		Lamp(T3DApplication *app);
		~Lamp(void);

		GameObject* base;
		GameObject* arm1;
		GameObject* arm2;
		GameObject* baseJoint;
		GameObject* elbowJoint;
		GameObject* shadeJoint;
	};
}

