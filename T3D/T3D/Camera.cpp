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

	// Safe default perspective camera
	Camera::Camera()
	{
		gameObject = 0;

		// Default perspective camera
		this->type = Camera::PERSPECTIVE;
		this->near = 0.1;
		this->far = 500.0;
		this->fovy = 45.0;
		this->aspect = 1.6;
	}

	// constructor with perspective parameters
	Camera::Camera(projectionType type, double near, double far, double fovy, double aspect)
	{
		gameObject = 0;

		this->type = type;				// this constructor assumes this should be PERSPECTIVE
		if (type != Camera::PERSPECTIVE)
			std::cout << "Incorrect constructor for " << type << std::endl;

		this->near = near;
		this->far = far;
		this->fovy = fovy;
		this->aspect = aspect;

		if (near <= 0.0)
			std::cout << "Camera's near clip plane is 0 or less " << near << std::endl;
	}

	// constructor with orthographic parameters
	Camera::Camera(projectionType type, double near, double far, double left, double right, double bottom, double top)
	{
		gameObject = 0;

		this->type = type;				// this constructor assumes this should be ORTHOGRAPHIC
		if (type != Camera::ORTHOGRAPHIC)
			std::cout << "Incorrect constructor for " << type << std::endl;

		this->near = near;
		this->far = far;
		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;
	}

	Camera::~Camera(void)
	{
	}

}
