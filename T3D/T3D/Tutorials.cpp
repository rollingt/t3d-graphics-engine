#include "Tutorials.h"
#include "Lamp.h"
#include "Camera.h"
#include "KeyboardController.h"

using namespace T3D;

bool T3D::Tutorials::init()
{
	WinGLApplication::init();	
	//Add a light
	GameObject* lightObj = new GameObject(this);
	Light* light = new Light(Light::DIRECTIONAL);
	light->setAmbient(1, 1, 1);
	light->setDiffuse(1, 1, 1);
	light->setSpecular(1, 1, 1);
	lightObj->setLight(light);
	lightObj->getTransform()->setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
	lightObj->getTransform()->setParent(root);
	//create a material
	Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
	grey->setDiffuse(0.8, 0.8, 0.9, 1);
	//create an instance of Lamp
	Lamp* lamp = new Lamp(this);
	lamp->setMaterial(grey);	
	lamp->base->setMaterial(grey);
	lamp->arm1->setMaterial(grey);
	lamp->arm2->setMaterial(grey);
	lamp->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	lamp->getTransform()->setParent(root);
	
	//add a camera to the scene
//This camera is super fast... you have been warned
	GameObject* camObj = new GameObject(this);
	renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
	camObj->getTransform()->setLocalPosition(Vector3(0, 0.5, 3));
	camObj->setCamera(renderer->camera);
	camObj->getTransform()->setParent(root);
	camObj->addComponent(new KeyboardController());			
	return true;
}
