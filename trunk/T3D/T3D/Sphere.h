// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// sphere.h
//
// A simple sphere mesh with variable size and polygon density

#ifndef SPHERE_H
#define SPHERE_H

#include "mesh.h"

namespace T3D{

	class Sphere :
		public Mesh
	{
	public:
		Sphere(float radius, int density = 8);
		virtual ~Sphere(void);
	};

}

#endif