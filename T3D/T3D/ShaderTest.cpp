// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// ShaderTest.cpp
//
// A simple application used for testing lighting shaders

#include "ShaderTest.h"
#include "Camera.h"
#include "Sphere.h"
#include "GLShader.h"

namespace T3D{

	ShaderTest::ShaderTest(void)
	{
	}


	ShaderTest::~ShaderTest(void)
	{
	}

	bool ShaderTest::init(){
		WinGLApplication::init();
		root->name = "Root";
		//test scene

		Material *shaderGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
		shaderGreen->setDiffuse(0,1,0,1);
		GLShader *specShader = new GLShader("Resources/vspecular.shader","Resources/frag.shader");
		specShader->compileShader();
		shaderGreen->setShader(specShader);

		Material *fixedGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
		fixedGreen->setDiffuse(0,1,0,1);

		GameObject *camObj = new GameObject(this);
		float near   = 0.1f;
		float far    = 500.0f;
		float fovy   = 45.0f;
		float aspect = 1.6f;

		renderer->camera = new Camera(near, far, fovy, aspect);
		camObj->getTransform()->setLocalPosition(Vector3(0,0,5));
		camObj->getTransform()->setLocalRotation(Vector3(0,0,0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::Type::DIRECTIONAL); 
		light->setAmbient(1,1,1);
		light->setDiffuse(1,1,1);
		light->setSpecular(1,1,1);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45*Math::DEG2RAD,70*Math::DEG2RAD,0));
		lightObj->getTransform()->setLocalPosition(Vector3(0,3,0));
		lightObj->getTransform()->setParent(root);

		GameObject *sphere1 = new GameObject(this);
		sphere1->setMesh(new Sphere(1.0,16));
		sphere1->setMaterial(shaderGreen);
		sphere1->getTransform()->setLocalPosition(Vector3(-1.25,0,0));		
		sphere1->getTransform()->setParent(root);
		sphere1->getTransform()->name = "Sphere 1";
		
		GameObject *sphere2 = new GameObject(this);
		sphere2->setMesh(new Sphere(1.0,16));
		sphere2->setMaterial(fixedGreen);
		sphere2->getTransform()->setLocalPosition(Vector3(1.25,0,0));		
		sphere2->getTransform()->setParent(root);
		sphere2->getTransform()->name = "Sphere 2";

		return true;
	}

}
