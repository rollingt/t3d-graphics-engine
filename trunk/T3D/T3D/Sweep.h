#ifndef SWEEP_H
#define SWEEP_H

#include <vector>
#include "mesh.h"
#include "Vector3.h"
#include "SweepPath.h"

namespace T3D
{
	///-------------------------------------------------------------------------------------------------
	/// @class	Sweep
	///
	/// @brief	Creates a 3D Mesh from a 2D profile by sweeping the profile around the y-axis.
	///
	/// @author	Rollingt
	/// @date	2/10/2013

	class Sweep :
		public Mesh
	{
	public:

		///-------------------------------------------------------------------------------------------------
		/// @fn	Sweep::Sweep(std::vector<Vector3> points, int density);
		///
		/// @brief	Constructor.
		///
		/// @author	Rollingt
		/// @date	2/10/2013
		///
		/// @param	points 	The points that define the sweep profile.  All points should be in the x-z plane
		/// @param	density	The number of profile instances that will be created as the profile is swept through 360 degrees.

		Sweep(std::vector<Vector3> points, SweepPath &path, bool closed = false);

		///-------------------------------------------------------------------------------------------------
		/// @fn	virtual Sweep::~Sweep(void);
		///
		/// @brief	Destructor.
		///
		/// @author	Rollingt
		/// @date	2/10/2013

		virtual ~Sweep(void);
	};
}

#endif