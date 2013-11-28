#ifndef PLANEMESH_H
#define PLANEMESH_H

#include "mesh.h"

namespace T3D{
	class PlaneMesh :
		public Mesh
	{
	public:
		PlaneMesh(int density);
		~PlaneMesh(void);

		void setVertex(int i, int j, float x, float y, float z);
		Vector3 getVertex(int i, int j);

		int density;
	};
}

#endif

