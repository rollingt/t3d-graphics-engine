#include "Tutorial4.h"
#include "Camera.h"
#include "KeyboardController.h"
#include "Cube.h"
#include "Pyramid.h"
using namespace T3D;


bool T3D::Tutorial4::init()

{
	//Add light to the scene 
	WinGLApplication::init();
	GameObject* lightObj = new GameObject(this);
	Light* light = new Light(Light::DIRECTIONAL);
	light->setAmbient(1, 1, 1);
	light->setDiffuse(1, 1, 1);
	light->setSpecular(1, 1, 1);
	lightObj->setLight(light);
	lightObj->getTransform()->
		setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
	lightObj->getTransform()->setParent(root);

	//Add camera and camera controller
	GameObject* camObj = new GameObject(this);
	renderer->camera =
		new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
	camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
	camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
	camObj->setCamera(renderer->camera);
	camObj->getTransform()->setParent(root);
	camObj->addComponent(new KeyboardController());

	//Add a material
	Material* green = renderer->createMaterial(Renderer::PR_OPAQUE);
	green->setDiffuse(0, 1, 0, 1);

	//Add a cube mesh for testing
	GameObject* cube = new GameObject(this);
	cube->setMesh(new Pyramid(1));
	cube->setMaterial(green);
	cube->getTransform()->setLocalPosition(Vector3(0, 0, 0));
	cube->getTransform()->setParent(root);
	cube->getTransform()->name = "Pyramid";


	return true;
}
