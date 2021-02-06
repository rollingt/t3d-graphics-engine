// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// KeyboardController.h
//
// Component to add flying controls to a game object
#pragma once

#include "Component.h"

namespace T3D
{
	//! \brief Add fly camera controls to a GameObject.
	class KeyboardController :
		public Component
	{
	public:
		KeyboardController(void);
		~KeyboardController(void) = default;

		virtual void update(float dt);
		void keyDownResolve(float dt);
		void keyUpResolve(float dt);
		void mouseMoveResolve();

	private:
		float keySensitivity,   keySensitivityMin,   keySensitivityMax;
		float mouseSensitivity, mouseSensitivityMin, mouseSensitivityMax;
	};

}
