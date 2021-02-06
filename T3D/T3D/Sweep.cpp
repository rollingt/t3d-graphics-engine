// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Sweep.cpp
//
// Create 3D meshes procedurally by moving ('sweeping') a 2D profile through space.

#include "Sweep.h"

namespace T3D
{
	/*
	 * \param points	Container of points defining a profile
	 * \param path		Path in world space to sweep profile along 
	 * \param closed	Loop the end of path back to beginning or not
	 */
	Sweep::Sweep(std::vector<Vector3> &profilePoints, SweepPath &path, bool closed) : Mesh()
	{
		/* Add an extra step to the sweep path if its closed */
		if (closed) path.addTransform(path[0]);

		// MSVC cannot inline `size()` calls for a vector that is mutable, as its possible
		// for the size to change during a loop body.
		// So, grab the sizes here and use them throughout the rest of the function as we know they don't change.
		const uint32_t pp = path.size();
		const uint32_t vp = profilePoints.size();

		int numVerts = pp * vp;
		int numQuads = numVerts;

	    /* triangles = 0 as not used */
		initArrays(numVerts, 0, numQuads);
		
		int vpos = 0;
		int fpos = 0;

		for (uint32_t i = 0; i < pp; i++) {
			for (uint32_t j = 0; j < vp; j++) {
				Vector3 v = path[i].transformPoint(profilePoints[j]);
				setVertex(vpos++,v.x,v.y,v.z);

				setQuadFace(fpos++,
							(j + 0)      + ( i + 0)       * vp,
							(j + 1) % vp + ( i + 0)       * vp,
							(j + 1) % vp + ((i + 1) % pp) * vp,
							(j + 0)      + ((i + 1) % pp) * vp);
			}
		}

		checkArrays();
		calcNormals();		
		
		int pos = 0;
		for (int i=0; i<numVerts; i++) {
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
	}

}
