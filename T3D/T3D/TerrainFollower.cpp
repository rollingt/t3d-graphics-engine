// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// TerrainFollower.cpp
//
// Simple behaviour for basic terrain following

#include "TerrainFollower.h"
#include "Transform.h"
#include "GameObject.h"

namespace T3D 
{
	/*
	 * \param dt Change in time
	 *
	 * \note The order in which T3D components update is _undefined_; beware multiple components updating world positions!
	 */
	void TerrainFollower::update(float dt) {
		Vector3 currentPos = gameObject->getTransform()->getWorldPosition();
		currentPos.y = terrain->getHeight(currentPos) + height;
		gameObject->getTransform()->setWorldPosition(currentPos);

		//Vector3 newPos = gameObject->getTransform()->getWorldPosition();
		//std::cout << currentPos << "->" << newPos << "\n";
	}

}
