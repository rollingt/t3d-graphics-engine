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
#include "Plane.h"
#include "GameObject.h"

namespace T3D
{
	// constructor with perspective parameters
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
			std::cout << "Camera's near clip plane is 0 or less " << near << std::endl;
			// TODO(Evan): Log!
		}
	}

	// constructor with orthographic parameters
	Camera::Camera(double near, double far, double left, double right, double bottom, double top) : Component()
	{
		this->type = Camera::Type::ORTHOGRAPHIC;
		this->near = near;
		this->far = far;
		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;

		/* Zeroed perspective parameters */
		this->fovy   = 0;
		this->aspect = 1.0f;
	}

}
