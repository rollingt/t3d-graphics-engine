// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// TerrainFollower.h
//
// Simple behaviour for basic terrain following
#pragma once

#include "Component.h"
#include "Terrain.h"

namespace T3D 
{
	//! \brief Component for following the surface of Terrain with respect to height.
	/*
	 * \note This looks best for convex Terrain with smooth slopes and GameObjects best visualized with bounding boxes.
	 */
	class TerrainFollower :
		public Component
	{
	public:
		//! \brief Create TerrainFollower
		/*
		 * \param t Terrain to 'follow'.
		 */
		TerrainFollower::TerrainFollower(Terrain* t, float h) : terrain(t),
															    height (h)  { }
		virtual ~TerrainFollower(void) = default;

		//! \brief Tick the TerrainFollower, updating the GameObject's height.
		virtual void update(float dt);

	private:
		Terrain* terrain;
		float height;
	};
}
