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

#ifndef COMPONENT_H
#define COMPONENT_H

namespace T3D
{
	class GameObject;

	class Component
	{
	public:
		Component(void) : gameObject(nullptr) { }
		virtual ~Component(void) = default;

		virtual void update(float dt)     { /* overridden */ };
		virtual void init(GameObject* go) { gameObject = go; };

	public:
		GameObject *gameObject;
	};
}

#endif
