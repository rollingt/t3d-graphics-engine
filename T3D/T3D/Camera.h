// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// camera.h
//
// Simple camera class to be attached to GameObject(s) and referenced from Renderer

#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Component.h"
#include "Plane.h"
#include "Transform.h"

namespace T3D
{
	class Camera :
		public Component
	{
	public:
		Camera(void);
		virtual ~Camera(void);

		void setView(double fovy, double aspect, double near, double far);	// set camera pespective

	public:
		double far;			// far z plane (distance from viewer)
		double near;		// near Z plane (distance from viewer)
		double fovy;		// field of view (angle in degrees)
		double aspect;		// field of view in X direction - ratio of x(width) to y(height)


	};
}

#endif

