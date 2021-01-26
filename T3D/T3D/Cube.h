// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.h
//
// Simple cube mesh with coloured sides

#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"

namespace T3D
{
	class Cube :
		public Mesh
	{
	public:
		// Create a cube with volume = size^3.
		Cube(float size);

		// Mesh deletes arrays if they have been created, not need to do anything here
		virtual ~Cube(void) = default;
	};
}

#endif

