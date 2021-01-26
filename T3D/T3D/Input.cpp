// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// input.cpp
//
// Simple static class to track keyboard and mouse
// Adapted from Ogre3D

#include "Input.h"

namespace T3D
{
	bool Input::keysDown[MAX_KEYS];
	int Input::mouseX = 0;
	int Input::mouseY = 0;

	void Input::init(){
		for (auto &key: keysDown) {
			key = false;
		}
		mouseX = 0; mouseY = 0;
	}

	void Input::onKeyDown(int keycode){
		keysDown[keycode] = true;
	}

	void Input::onKeyUp(int keycode){
		keysDown[keycode] = false;
	}

	void Input::onMouseMotion(int dx, int dy){
		mouseX = dx;
		mouseY = dy;
	}

}
