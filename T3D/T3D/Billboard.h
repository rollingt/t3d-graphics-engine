// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Billboard.cpp
//
// A billboard component.  Creates a plane mesh and adds it to the game object.  
// Update method supports spherical and cylindrical billboarding to face the plane towards the camera

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
		// Creates a Billboard associated with a Camera. May rotate about the Y axis by default.
		// A Billboard should be initialised with a parent GameObject using its init method before it can be used.
		Billboard(Transform* camera, bool lockY = false) : lockY(lockY),
		                                                   camera(camera) { };
		~Billboard(void) = default;

		// Update the Billboard's facing every frame to ensure it's looking at the camera.
		virtual void update(float dt);
		virtual void init(GameObject* go);

		// Helper functions.
		void lockYAxis()  { lockY = true; }
		void unlockYAxis(){ lockY = false; }

	private:
		Transform* camera;
		bool lockY;
	};
}

#endif
