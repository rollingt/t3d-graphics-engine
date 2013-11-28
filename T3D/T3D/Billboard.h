#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "component.h"
#include "Transform.h"

namespace T3D
{
	class Billboard :
		public Component
	{
	public:
		Billboard(Transform* camera, bool lockY = false) : lockY(lockY),camera(camera){};
		~Billboard(void);

		virtual void update(float dt);
		virtual void init(GameObject* go);

		void lockYAxis(){ lockY = true; }
		void unlockYAxis(){ lockY = false; }

	private:
		Transform* camera;
		bool lockY;
	};
}

#endif