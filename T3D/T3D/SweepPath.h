// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// SweepPath.h
//
// Helpful operations for creating common sweep paths such as circles.
#pragma once

#include <vector>
#include "Transform.h"

namespace T3D
{
	class SweepPath
	{
	public:
		//! \brief Create SweepPath (trivially)
		SweepPath(void) = default;

		//! \brief Destroy SweepPath (trivially)
		virtual ~SweepPath(void) = default;

		//! \brief Add Transform to end of the Path.
		void addTransform(Transform &t);

		//! \brief Get number of Transforms in the path.
		uint32_t size(){ return path.size(); }

		//! \brief Create a circular path.
		void makeCirclePath(float radius, int density);

		//! \brief Get a Transform from the path.
		Transform operator[](int index) const;

	protected:
		std::vector<Transform> path;
	};
}
