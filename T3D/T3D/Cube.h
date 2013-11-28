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
		Cube(float size);
		virtual ~Cube(void);
	};
}

#endif

