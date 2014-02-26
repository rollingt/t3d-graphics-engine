// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// t3dtest.cpp
//
// Example t3dapplication

#include "t3dtest.h"
#include "Cube.h"
#include "PlaneMesh.h"
#include "Sphere.h"
#include "KeyboardController.h"
#include "TerrainFollower.h"
#include "RotateBehaviour.h"
#include "LookAtBehaviour.h"
#include "Terrain.h"
#include "Camera.h"
#include "ParticleEmitter.h"
#include "ParticleBehaviour.h"
#include "PerfLogTask.h"
#include "DiagMessageTask.h"
#include "Material.h"
#include "Animation.h"
#include "Billboard.h"
#include "Math.h"
#include "Sweep.h"
#include "SweepPath.h"

namespace T3D{

	T3DTest::T3DTest(void)
	{
	}


	T3DTest::~T3DTest(void)
	{
	}

	bool T3DTest::init(){
		// Call init of superclass (sets up sdl and opengl)
		WinGLApplication::init();

		//Create a skybox and add some fog
		renderer->loadSkybox("Resources/Sunny1");
		renderer->setFog(0.007f,0.8f,0.8f,0.8f,1.0f);
		renderer->toggleFog();

		//Add a light
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::DIRECTIONAL); 
		light->setAmbient(1,1,1);
		light->setDiffuse(1,1,1);
		light->setSpecular(1,1,1);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45*Math::DEG2RAD,70*Math::DEG2RAD,0));
		lightObj->getTransform()->setParent(root);

		//Create some basic materials
		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1,0,0,1);
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0,1,0,1);
		Material *blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0,0,1,1);

		//Create some textured materials (using texture files)
		Texture *smileytex = new Texture("Resources/Smiley.bmp", true, true);
		renderer->loadTexture(smileytex);
		Material *smiley = renderer->createMaterial(Renderer::PR_OPAQUE);
		smiley->setTexture(smileytex);
		
		Texture *sparkletex = new Texture("Resources/sparkle.png", true, true);
		renderer->loadTexture(sparkletex);
		Material *sparklemat = renderer->createMaterial(Renderer::PR_TRANSPARENT);
		sparklemat->setEmissive(1, 1, 1, 1);
		sparklemat->setBlending(Material::BLEND_DEFAULT);
		sparklemat->setSortedDraw(true, false);
		sparklemat->setTexture(sparkletex);

		//Create a textured material by adding text
		Texture *texttex = new Texture(128,32);
		texttex->clear(Colour(255,255,255,255));
		font *f = getFont("resources/FreeSans.ttf", 24);
		if (f != NULL) {
			texttex->writeText(2, 0, "Hello", Colour(0,255,0,255), f->getFont());
			texttex->writeText(64, 0, "World", Colour(255,0,0,0), f->getFont());
		}
		renderer->loadTexture(texttex, true);		
		Material *textmat = renderer->createMaterial(Renderer::PR_OPAQUE);
		textmat->setTexture(texttex,1);
		textmat->setEmissive(1,1,1,1);
				
		//Create a material with a procedurally generated texture
		Texture *proctex = new Texture(512,512);
		proctex->createFractal(Colour(40,150,50,255),Colour(120,220,100,255),25.0f,false);
		renderer->loadTexture(proctex, true);		
		Material *procmat = renderer->createMaterial(Renderer::PR_TERRAIN);
		procmat->setTexture(proctex,50);
		procmat->setSpecular(0,0,0,0);

		//Create a camera
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0,0,20));
		camObj->getTransform()->setLocalRotation(Vector3(0,0,0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);

		//Add a controller to the camera object
		camObj->addComponent(new KeyboardController());

		//Add some terrain
		GameObject *terrain = new GameObject(this);
		Terrain *terrainComponent = new Terrain();
		terrain->addComponent(terrainComponent);
		terrainComponent->createFractalTerrain(256,500,15,2.0); // procedurally generate terrain
		terrain->setMaterial(procmat);
		terrain->getTransform()->setLocalPosition(Vector3(0,-20,0));
		terrain->getTransform()->setParent(root);
		terrain->getTransform()->name = "Terrain";

		//Add a welcome message
		GameObject *billboard = new GameObject(this);
		Billboard *billboardComponent = new Billboard(renderer->camera->gameObject->getTransform(),true);
		billboard->addComponent(billboardComponent);
		billboard->setMaterial(textmat);			// hello world
		billboard->getTransform()->setLocalPosition(Vector3(0,3,0));
		billboard->getTransform()->setLocalScale(Vector3(6,1.5,1));
		billboard->getTransform()->setParent(root);
		billboard->getTransform()->name = "Billboard";

		//Add a cube mesh
		GameObject *cube = new GameObject(this);
		cube->setMesh(new Cube(1));
		cube->setMaterial(smiley);
		cube->getTransform()->setLocalPosition(Vector3(4,-3,0));
		cube->getTransform()->setParent(root);
		cube->getTransform()->name = "Cube";

		//Create an empty node to use as a rotation point
		GameObject *rotateOrigin = new GameObject(this);
		rotateOrigin->getTransform()->setParent(root);
		rotateOrigin->addComponent(new RotateBehaviour(Vector3(0,1,0)));
		
		//Create a torus using the Sweep class as a child of rotateOrigin
		SweepPath sp;
		sp.makeCirclePath(2,32);
		GameObject *torus = new GameObject(this);
		vector<Vector3> points;
		points.push_back(Vector3(0.2f,0.0f,0.0f));
		points.push_back(Vector3(0.14f,0.14f,0.0f));
		points.push_back(Vector3(0.0f,0.2f,0.0f));
		points.push_back(Vector3(-0.14f,0.14f,0.0f));
		points.push_back(Vector3(-0.2f,0.0f,0.0f));
		points.push_back(Vector3(-0.14f,-0.14f,0.0f));
		points.push_back(Vector3(0.0f,-0.2f,0.0f));
		points.push_back(Vector3(0.14f,-0.14f,0.0f));
		torus->setMesh(new Sweep(points,sp,true));
		torus->setMaterial(red);
		torus->getTransform()->setLocalPosition(Vector3(10,0,0));
		torus->getTransform()->setParent(rotateOrigin->getTransform());
		torus->getTransform()->name = "Torus";

		//Add a sphere mesh as a child of the torus
		GameObject *sphere = new GameObject(this);
		sphere->setMesh(new Sphere(0.5,32));
		sphere->setMaterial(blue);
		sphere->getTransform()->setLocalPosition(Vector3(0,5,0));	
		sphere->getTransform()->setParent(torus->getTransform());
		sphere->getTransform()->name = "Sphere";
		
		//Create some animation for the sphere and torus
		Animation *anim = new Animation(10.0);
		torus->addComponent(anim);
		anim->addKey("Sphere",10.0,Quaternion(),Vector3(0,5,0));
		anim->addKey("Sphere",0,Quaternion(),Vector3(0,5,0));
		anim->addKey("Sphere",7.0,Quaternion(),Vector3(0,0,0));
		anim->addKey("Sphere",5.0,Quaternion(),Vector3(0,-5,0));
		anim->addKey("Torus",10.0,Quaternion(),Vector3(10,0,0));
		anim->addKey("Torus",0,Quaternion(),Vector3(10,0,0));
		anim->addKey("Torus",7.0,Quaternion(),Vector3(15,0,0));
		anim->addKey("Torus",5.0,Quaternion(Vector3(0,0,Math::HALF_PI)),Vector3(5,0,0));
		anim->loop(true);	
		
		//Add a particle system to the sphere
		ParticleEmitter *particleSys = new ParticleEmitter(0.0f, 20.0f, 20.0f, 20.0f, 5.0f, 5.0f, 0.2f);
		sphere->addComponent(particleSys);
		particleSys->createBillboardParticles(100, 1.0, 1.0, sparklemat, 1.0, root);
		particleSys->setPositionRange(0.01f, 0.01f, 0.01f);
		particleSys->setDirection(0*Math::DEG2RAD, 0.0*Math::DEG2RAD, 180*Math::DEG2RAD);
		particleSys->setStartVelocity(20.0f, 20.0f);
		particleSys->setAcceleration(-30.0f, 1.0f);
		particleSys->setAlphaFade(1.0f, 0.0f);
		particleSys->emit(40);
		
		//Add a behaviour to the Cube to make it "look at" the sphere
		cube->addComponent(new LookAtBehaviour(sphere->getTransform()));

		//Add a help overlay
		addTask(new DiagMessageTask(this, "Press F9 for help", 2, 32, true, 5.0));

		return true;
	}
}