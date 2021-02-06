// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// PlaneMesh.h
//
// Create a Mesh from a Plane representation
// Adapted from Ogre3D
#pragma once

#include "Mesh.h"

namespace T3D
{
	class PlaneMesh :
		public Mesh
	{
	public:
		PlaneMesh(int density);
		~PlaneMesh(void) = default;

		void setVertex(int i, int j, float x, float y, float z);
		Vector3 getVertex(int i, int j);

		int density;
	};
}
