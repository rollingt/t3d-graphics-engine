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

namespace T3D
{
	//min and max speeds for key and mouse sensitivity
	#define KEY_SENSITIVITY_MIN 50
	#define KEY_SENSITIVITY_MAX 100
	#define MOUSE_SENSITIVITY_MIN 0.0005;
	#define MOUSE_SENSITIVITY_MAX 0.0010;

	KeyboardController::KeyboardController(void)
	{
		keySensitivity = 50.0;
		mouseSensitivity = 0.0005;
	}


	KeyboardController::~KeyboardController(void)
	{
	}

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

		if (Input::keyDown[KEY_LEFT] || Input::keyDown[KEY_A]){
			gameObject->getTransform()->move(-right*dt*keySensitivity);
		}
		if (Input::keyDown[KEY_RIGHT] || Input::keyDown[KEY_D]){
			gameObject->getTransform()->move(right*dt*keySensitivity);
		}
		if (Input::keyDown[KEY_UP] || Input::keyDown[KEY_W]){
			gameObject->getTransform()->move(-back*dt*keySensitivity);
		}
		if (Input::keyDown[KEY_DOWN] || Input::keyDown[KEY_S]){
			gameObject->getTransform()->move(back*dt*keySensitivity);
		}

		if (Input::keyDown[KEY_SPACE]){
			gameObject->getTransform()->move(up*dt*keySensitivity);
		}
		if (Input::keyDown[KEY_LEFT_CONTROL]){
			gameObject->getTransform()->move(-up*dt*keySensitivity);
		}

		if (Input::keyDown[KEY_LEFT_SHIFT]){
			keySensitivity = KEY_SENSITIVITY_MAX;
			mouseSensitivity = MOUSE_SENSITIVITY_MAX;
		}

	}

	//Method to resolve the actions of each keyUp event, following keyDown
	void KeyboardController::keyUpResolve(float dt){
		
		if (!Input::keyDown[KEY_LEFT_SHIFT]){
			keySensitivity = KEY_SENSITIVITY_MIN;
			mouseSensitivity = MOUSE_SENSITIVITY_MIN;
		}

	}

	//Method to resolve the action of mouse movements
	void KeyboardController::mouseMoveResolve(){

		Vector3 rotation = gameObject->getTransform()->getEulerAngles();

		rotation += Vector3(-Input::mouseY*mouseSensitivity, -Input::mouseX*mouseSensitivity, 0);
		float eightydeg = 80 * Math::DEG2RAD;
		if (rotation.x > eightydeg) rotation.x = eightydeg;
		if (rotation.x < -eightydeg) rotation.x = -eightydeg;

		gameObject->getTransform()->setLocalRotation(rotation);
	}

}
