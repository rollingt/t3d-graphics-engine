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
		typedef enum {
			PERSPECTIVE,
			ORTHOGRAPHIC
		} projectionType;

		// Safe default perspective camera
		Camera();
		// constructor optimised with perspective parameters
		Camera(projectionType type, double near, double far, double fovy, double aspect);
		// constructor with orthographic parameters
		Camera(projectionType type, double near, double far, double left, double right, double bottom, double top);
		virtual ~Camera();

	public:
		projectionType type;	// projection type

		double far;				// far z plane (distance from viewer)
		double near;			// near Z plane (distance from viewer)

		// Perspectve projection only
		double fovy;			// field of view (angle in degrees)
		double aspect;			// field of view in X direction - ratio of x(width) to y(height)

		// Orthographic only
		double left,right,top,bottom;	// view extent

	};
}

#endif

