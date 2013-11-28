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
		far = 1000.0;
	}


	Camera::~Camera(void)
	{
	}

}
