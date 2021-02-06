// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// component.h
//
// Abstract component class for game objects
// Used to add behaviours and other functionality to game objects
// Automatically updated by application
#pragma once

namespace T3D
{
	class GameObject;

	//! \brief Components are used to add functionality (or behaviour) to GameObjects, using a 'has-a' relationship. A GameObject can have zero or more components.
	class Component
	{
	public:
		//! \brief Create a Component.
		Component(void) : gameObject(nullptr) { }

		//! \brief Destroy a Component.
		virtual ~Component(void) = default;

		//! \brief Tick the Component.
		virtual void update(float dt)     { /* overridden */ };

		//! \brief Initialize the Component to be associated with a GameObject.
		/*!
		 * \param go GameObject to associate with this component. 
		 */
		virtual void init(GameObject* go) { gameObject = go; };

		//! \brief GameObject that 'has' this Component
		GameObject *gameObject;
	};
}
