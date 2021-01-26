// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// keyboardcontroller.h
//
// Component to add FPS-like controls to a game object

#include <iostream>

#include "KeyboardController.h"
#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"
#include "DefaultDebugOptions.h"

namespace T3D
{

	KeyboardController::KeyboardController(void) : /* Defaults */
												   keySensitivity     (DefaultDebugOptions::keySensitivityMin),
												   keySensitivityMin  (DefaultDebugOptions::keySensitivityMin),
												   keySensitivityMax  (DefaultDebugOptions::keySensitivityMax),
												   mouseSensitivity   (DefaultDebugOptions::mouseSensitivityMin),
												   mouseSensitivityMin(DefaultDebugOptions::mouseSensitivityMin),
												   mouseSensitivityMax(DefaultDebugOptions::mouseSensitivityMax)
	{ /* Initialiser List */ }

	void KeyboardController::update(float dt){

		//resolve all of the input actions
		keyDownResolve(dt);
		keyUpResolve(dt);
		mouseMoveResolve();
		
	}

	//Method to resolve the actions of each keyDown event
	void KeyboardController::keyDownResolve(float dt)
	{
		Matrix4x4 m = gameObject->getTransform()->getLocalMatrix();
		Vector3 right = Vector3(m[0][0], m[1][0], m[2][0]);
		Vector3 up = Vector3(m[0][1], m[1][1], m[2][1]);
		Vector3 back = Vector3(m[0][2], m[1][2], m[2][2]);

		if (Input::keysDown[KEY_LEFT] || Input::keysDown[KEY_A]){
			gameObject->getTransform()->move(-right*dt*keySensitivity);
		}
		if (Input::keysDown[KEY_RIGHT] || Input::keysDown[KEY_D]){
			gameObject->getTransform()->move(right*dt*keySensitivity);
		}
		if (Input::keysDown[KEY_UP] || Input::keysDown[KEY_W]){
			gameObject->getTransform()->move(-back*dt*keySensitivity);
		}
		if (Input::keysDown[KEY_DOWN] || Input::keysDown[KEY_S]){
			gameObject->getTransform()->move(back*dt*keySensitivity);
		}

		if (Input::keysDown[KEY_SPACE]){
			gameObject->getTransform()->move(up*dt*keySensitivity);
		}
		if (Input::keysDown[KEY_LEFT_CONTROL]){
			gameObject->getTransform()->move(-up*dt*keySensitivity);
		}

		if (Input::keysDown[KEY_LEFT_SHIFT]){
			keySensitivity = keySensitivityMax;
			mouseSensitivity = mouseSensitivityMax;
		}

	}

	//Method to resolve the actions of each keyUp event, following keysDown
	void KeyboardController::keyUpResolve(float dt){
		
		if (!Input::keysDown[KEY_LEFT_SHIFT]){
			keySensitivity   = keySensitivityMin;
			mouseSensitivity = mouseSensitivityMin;
		}

	}

	//Method to resolve the action of mouse movements
	void KeyboardController::mouseMoveResolve(){

		Vector3 rotation = gameObject->getTransform()->getEulerAngles();

		rotation += Vector3(-Input::mouseY*mouseSensitivity, -Input::mouseX*mouseSensitivity, 0);
		float eightydeg = 80 * Math::DEG2RAD; // Prevent horizontal and up vector from becoming orthoganal!
		if (rotation.x > eightydeg) rotation.x = eightydeg;
		if (rotation.x < -eightydeg) rotation.x = -eightydeg;

		gameObject->getTransform()->setLocalRotation(rotation);
	}

}
