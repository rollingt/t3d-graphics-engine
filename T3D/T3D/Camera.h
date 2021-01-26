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

#include "Component.h"
#include "Plane.h"
#include "Transform.h"

namespace T3D
{
	class Camera :
		public Component
	{
	public:
		enum class Type 
		{
			PERSPECTIVE,
			ORTHOGRAPHIC
		};

		// Safe default perspective camera
		Camera::Camera() : type      (Camera::Type::PERSPECTIVE),
						   near      (0.1),
						   far       (500.0),
						   fovy      (45.0),
						   aspect    (1.6) ,
						   left      (0), 
						   right     (0), 
						   bottom    (0), 
						   top       (0)
		{ }

		// Perspective Camera
		Camera(double near, double far, double fovy, double aspect);
		// Orthographic Camera
		Camera(double near, double far, double left, double right, double bottom, double top);

		virtual ~Camera() = default;

	public:
		Type type;	// projection type

		double far;				// far z plane (distance from viewer)
		double near;			// near Z plane (distance from viewer)

		// Perspective projection only
		double fovy;			// field of view (angle in degrees)
		double aspect;			// field of view in X direction - ratio of x(width) to y(height)

		// Orthographic only
		double left,right,top,bottom;	// view extent

	};
}

#endif

