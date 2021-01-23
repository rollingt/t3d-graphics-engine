// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Billboard.cpp
//
// A billboard component.  Creates a plane mesh and adds it to the game object.  
// Update method supports spherical and cylindrical billboarding to face the plane towards the camera

#include "Billboard.h"
#include "PlaneMesh.h"
#include "GameObject.h"
#include "T3DApplication.h"
#include "Camera.h"

namespace T3D
{
	// Initialise the Billboard component with its parent GameObject.
	void Billboard::init(GameObject* go){
		gameObject = go;
		
		PlaneMesh *mesh = new PlaneMesh(10); 
		gameObject->setMesh(mesh);
	}
	
	// Update the Billboard's facing every frame to ensure it's looking at the camera.
	void Billboard::update(float dt){	
		Vector3 camera = this->camera->getWorldPosition();

		if (lockY){
			camera.y = gameObject->getTransform()->getWorldPosition().y;
		}

		// Billboards require a 'special case' when using lookAt. 
		// The lookAt matrix is defined with respect to the difference vector between the local and target transform, and an 'eye' (or camera) vector.
		// When the camera is both the target _and_ the world-view camera in a right-hand coordinate system (i.e. OpenGL as in T3D), we need to compensate
		// for the fact it is already 'looking down' the negative z axis, otherwise the XZ planemesh defining a billboard will be inverted.
		auto *transform = gameObject->getTransform();
		auto billboard_plane = transform->getWorldPosition();

		transform->lookAt(billboard_plane - camera);
		Quaternion q  = Quaternion::fromAngleAxis(Math::HALF_PI, Vector3(1,0,0));
		transform->rotate(q);
	}

}
