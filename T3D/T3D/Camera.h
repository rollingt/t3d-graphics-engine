// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// camera.h
//
// Simple camera class to be attached to GameObject(s) and referenced from Renderer
#pragma once

#include "Component.h"

namespace T3D
{
	//! \brief A camera for viewing the scene. Can be perspective or orthographic.
	/*!
	 *	Camera's are associated with a GameObject, like all Components. An idiom in T3D is to attach a Camera and KeyboardController component to a GameObject to act as a fly camera.
	 */
	class Camera :
		public Component
	{
	public:

		//! \brief What type of Camera an instance is
		enum class Type 
		{
			PERSPECTIVE,
			ORTHOGRAPHIC
		};

		//! \brief Create a perspective camera with safe defaults.
		Camera::Camera() : Component(), 
						   type      (Camera::Type::PERSPECTIVE),
						   near      (0.1),
						   far       (500.0),
						   fovy      (45.0),
						   aspect    (1.6) ,
						   left      (0), 
						   right     (0), 
						   bottom    (0), 
						   top       (0)
		{ }

		//! \brief Create a perspective camera.
		Camera(double near, double far, double fovy, double aspect);

		//! \brief Create an orthographic camera.
		Camera(double near, double far, double left, double right, double bottom, double top);

		//! \brief Destroy the camera.
		virtual ~Camera() = default;

	public:
		//! \brief Projection type
		Camera::Type type;

		//! \brief far Z plane (distance from viewer)
		double far;				
		//! \brief near Z plane (distance from viewer)
		double near;

		/* Perspective projection only */
		//! \brief field of view (angle in degrees)
		double fovy;
		//! \brief field of view in X direction - ratio of x(width) to y(height)
		double aspect;

		/* Orthographic only */
		//! \brief planes of view extent/frustrum 
		double left, right, top, bottom;

	};
}
