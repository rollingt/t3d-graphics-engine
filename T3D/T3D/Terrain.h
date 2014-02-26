// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Terrain.h
//
// Component used for creating terrains - from an image file, or procedurally.

#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include "component.h"
#include "Vector3.h"

namespace T3D{

	//! A triangle mesh terrain class
	/*! Can create a terrain from a texture or procudurally generate a fractal terrain
	  \todo		Consider refactoring this class so that it is a subclass of Mesh
	  
	  \author	Robert Ollington
	  */

	class Terrain :
		public Component
	{
	public:
		Terrain();
		virtual ~Terrain(void);

		float getHeight(Vector3 pos);

		void createTerrain(std::string tex, float horizScale, float vertScale);
		void createFractalTerrain(int resolution, float horizScale, float vertScale, float roughness);

		float size;
		float gridSize;
	};

}

#endif

