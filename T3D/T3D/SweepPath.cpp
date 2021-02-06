// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// SweepPath.h
//
// Helpful operations for creating common sweep paths such as circles.

#include "SweepPath.h"

namespace T3D{

	Transform SweepPath::operator[](int index) const {
		return path[index];
	}

	/*
	 * \param t Transform to add
	 */
	void SweepPath::addTransform(Transform &t) {
		path.push_back(t);
	}

	/*
	 * \param radius Path radius
	 * \param density Vertices in path
	 *
	 * \note This will *clear* any transforms that are already in the Path!
	 */
	void SweepPath::makeCirclePath(float radius, int density){
		path.clear();
		for (int i=0; i<density; i++){
			Transform t;
			float angle = Math::TWO_PI*i/density;
			t.setLocalPosition(Vector3(radius*cosf(angle),0, radius*std::sinf(angle)));
			t.setLocalRotation(Quaternion(Vector3(0,-angle,0)));
			path.push_back(t);
		}

	}

}
