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

	public:
		float far;
	};
}

#endif

