// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Terrain.h
//
// Component used for creating terrains - from an image file, or procedurally.
#pragma once

#include <string>

#include "Component.h"
#include "Vector3.h"

namespace T3D {

	//! \brief Create Terrain from heightmaps, or procedurally.
	/*! 
	 * Can create a terrain from a texture or procudurally generate a fractal terrain
	 * \todo Consider refactoring this class so that it is a subclass of Mesh
	 * 
	 * \author	Robert Ollington
	 */
	class Terrain :
		public Component
	{
	public:
		Terrain() : size(0), gridSize(0) { }
		virtual ~Terrain(void) = default;

		float getHeight(Vector3 pos);

		void createTerrain(std::string tex, float horizScale, float vertScale);
		void createFractalTerrain(int resolution, float horizScale, float vertScale, float roughness);

		float size;
		float gridSize;
	};

}
