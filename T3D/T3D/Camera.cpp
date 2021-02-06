// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// camera.cpp
//
// Simple camera class to be attached to GameObject(s) and referenced from Renderer

#include "Camera.h"
#include "Logger.h"

namespace T3D
{
	/*!
	 * \param near Near clip plane distance. If <= 0, a warning is issued.
	 * \param far Far clip plane distance.
	 * \param fovy Field of view spanning 'y' in *degrees*.
	 * \param aspect Aspect ratio. Most monitors are 16:9, so (16.0/9.0) works.
	 *
	 * \note The ratio between near and far should be kept small. The depth buffer of a scene is non-linear so it will lose a lot of precision over distances with a very small near clip plane. The near plane should be as far away from 0 as possible. 
	 */
	Camera::Camera(double near, double far, double fovy, double aspect) : Component()
	{
		this->type = Camera::Type::PERSPECTIVE;
		this->near = near;
		this->far = far;
		this->fovy = fovy;
		this->aspect = aspect;

		/* Zeroed orthographic parameters */
		this->left   = 0;
		this->right  = 0;
		this->bottom = 0;
		this->top    = 0;

		if (near <= 0.0)
		{
			logger::Log(priority::Warning, 
						output_stream::File, 
						category::Video, 
						"Camera's near clip plane is 0 or less! Near: %.4f\n"
						,
						near);
		}
	}

	/*!
	 * \param near Near clip plane distance. If <= 0, a warning is issued.
	 * \param far Far clip plane distance.
	 * \param left Left plane of frustrum
	 * \param right Right plane of frustrum
	 * \param bottom Bottom plane of frustrum
	 * \param top Top plane of frustrum
	 *
	 * \note The ratio between near and far should be kept small. The depth buffer of a scene is non-linear so it will lose a lot of precision over distances with a very small near clip plane. The near plane should be as far away from 0 as possible. 
	 */
	Camera::Camera(double near, double far, double left, double right, double bottom, double top) : Component()
	{
		this->type = Camera::Type::ORTHOGRAPHIC;
		this->near = near;
		this->far = far;
		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;

		/* Default perspective parameters */
		this->fovy   = 0;
		this->aspect = 1.0f;

		if (near <= 0.0)
		{
			logger::Log(priority::Warning, 
						output_stream::File, 
						category::Video, 
						"Camera's near clip plane is 0 or less! Near: %.4f\n"
						,
						near);
		}
	}

}
