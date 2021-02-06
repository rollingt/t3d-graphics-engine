// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Sphere.h
//
// A simple sphere mesh with variable size and polygon density.
#pragma once

#include "Mesh.h"

namespace T3D {

	// \! Simple parametric Sphere mesh.
	class Sphere :
		public Mesh
	{
	public:
		//! \brief Create Sphere.
		/*
		 * \param radius	Radius of sphere
		 * \param density	Number of planes cubed that defines a Sphere.
		 *
		 */
		Sphere(float radius, int density = 8);

		//! \brief Destroy Sphere (trivially)
		virtual ~Sphere(void) = default;
	};

}
