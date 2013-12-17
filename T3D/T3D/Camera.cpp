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

	Camera::Camera(void)
	{
		gameObject = 0;

		// safe defaults for camera perspective and clip planes
		fovy = 45.0;
		aspect = 1.6;
		near = 0.1;
		far = 500.0;
	}

	Camera::~Camera(void)
	{
	}

	// set camera pespective and clipping planes (sets the camera frustum)
	void Camera::setView(double fovy, double aspect, double near, double far)
	{
		this->fovy = fovy;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		if (near <= 0.0)
			std::cout << "Camera near clip plane 0 or less " << near << std::endl;
	}

}
