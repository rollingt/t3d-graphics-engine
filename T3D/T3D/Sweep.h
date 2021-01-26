#ifndef SWEEP_H
#define SWEEP_H

#include <vector>
#include "mesh.h"
#include "Vector3.h"
#include "SweepPath.h"

namespace T3D
{
	//! Creates a 3D Mesh from a (usually 2D) profile by sweeping the profile along a SweepPath
	/*! The profile is defined by a list of Vector3's (2D profile recommended). The SweepPath is defined by a list of Transform's.  
	  Care must be taken to ensure that the profile and path define a valid mesh - no error checking is performed
	  \author	Robert Ollington
	  */
	class Sweep :
		public Mesh
	{
	public:
		Sweep(std::vector<Vector3> &points, SweepPath &path, bool closed = false);
		virtual ~Sweep(void) = default;
	};
}

#endif
