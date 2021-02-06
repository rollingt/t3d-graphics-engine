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
#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

namespace T3D
{
	//! \brief Billboard is a wrapper around a plane mesh. Every frame, the billboard will face the camera.
	/*!
	 *	You will want to add a Billboard to a GameObject that has a textured `Material`, otherwise it won't be very exciting, or visible.
	 */
	class Billboard :
		public Component
	{
	public:

		//! \brief Creates a Billboard associated with a Camera. May rotate about the Y axis by default.
		/*!
		 * \param camera	Camera billboard should face
		 * \param lockY		Can the billboard move about the Y axis? ('yaw')
		 *
		 * \note A Billboard should be initialised with a parent GameObject using its init method before it can be used.
		 */
		Billboard(Transform* camera, bool lockY = false) : lockY(lockY),
		                                                   camera(camera) { };
		//! \brief Destroy the billboard.
		~Billboard(void) = default;

		//! \brief Update the Billboard's facing every frame to ensure it's looking at the camera.
		virtual void update(float dt);

		//! \brief Destroy the billboard.
		virtual void init(GameObject* go);

		// Helper functions. Inlined because they're so small.


		//! \brief Set the Y axis to be locked.
		void lockYAxis()  { lockY = true; }

		//! \brief Set the Y axis to be unlocked.
		void unlockYAxis(){ lockY = false; }

	private:
		//! \brief Transform of the Camera to face
		Transform* camera;

		//! \brief Can the billboard move about the Y axis?
		bool lockY;
	};
}
