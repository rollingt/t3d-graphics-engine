// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// t3dtest.cpp
//
// Example t3dapplication
// Creates cube, sphere, camera and light
// Adds keyboard controller to camera game object
// Adds perflogtask

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
		WinGLApplication::init();
		root->name = "Root";
		//test scene

		renderer->loadSkybox("Resources/Sunny1");	

		renderer->setFog(0.007,0.8,0.8,0.8,1.0);
		renderer->toggleFog();

		Material *red = renderer->createMaterial(Renderer::PR_OPAQUE);
		red->setDiffuse(1,0,0,1);
		Material *green = renderer->createMaterial(Renderer::PR_OPAQUE);
		green->setDiffuse(0,1,0,1);
		green->setFlat();
		green->setSpecular(0,0,0,0);
		Material *blue = renderer->createMaterial(Renderer::PR_OPAQUE);
		blue->setDiffuse(0,0,1,1);

		Texture *smileytex = new Texture("Resources/Smiley.bmp", true, true);
		renderer->loadTexture(smileytex);
		Material *smiley = renderer->createMaterial(Renderer::PR_OPAQUE);
		smiley->setTexture(smileytex);

		Texture *flametex = new Texture("Resources/flames.png", true, true);
		renderer->loadTexture(flametex);
		Material *flamemat = renderer->createMaterial(Renderer::PR_TRANSPARENT);
		//flamemat->setBlending(Material::BLEND_DEFAULT);
		flamemat->setTexture(flametex);

		Texture *proctex = new Texture(512,512);
		proctex->createFractal(Colour(40,150,50,255),Colour(120,220,100,255),25.0f,false);
		renderer->loadTexture(proctex, true);		
		Material *procmat = renderer->createMaterial(Renderer::PR_TERRAIN);
		procmat->setTexture(proctex,50);
		procmat->setSpecular(0,0,0,0);


		cout << "creating camera\n";
		GameObject *camObj = new GameObject(this);
		renderer->camera = new Camera(Camera::PERSPECTIVE, 0.1, 500.0, 45.0, 1.6);
		camObj->getTransform()->setLocalPosition(Vector3(0,0,20));
		camObj->getTransform()->setLocalRotation(Vector3(0,0,0));
		//renderer->camera = new Camera(Camera::ORTHOGRAPHIC, 0.1, 500.0, -16, 16, -10, 10);
		//camObj->getTransform()->setLocalPosition(Vector3(0,20,0));
		//camObj->getTransform()->setLocalRotation(Vector3(-90*Math::DEG2RAD,0,0));
		camObj->setCamera(renderer->camera);
		camObj->getTransform()->setParent(root);
		camObj->addComponent(new KeyboardController());

		cout << "creating light\n";
		GameObject *lightObj = new GameObject(this);
		Light *light = new Light(Light::DIRECTIONAL); 
		light->setAmbient(1,1,1);
		light->setDiffuse(1,1,1);
		light->setSpecular(1,1,1);
		lightObj->setLight(light);
		lightObj->getTransform()->setLocalRotation(Vector3(-45*Math::DEG2RAD,70*Math::DEG2RAD,0));
		lightObj->getTransform()->setParent(root);

		cout << "creating cube\n";
		GameObject *cube = new GameObject(this);
		cube->setMesh(new Cube(1));
		cube->setMaterial(smiley);
		cube->getTransform()->setLocalPosition(Vector3(0,0,0));
		cube->getTransform()->setParent(root);
		cube->getTransform()->name = "Cube";

		cout << "creating plane\n";
		GameObject *terrain = new GameObject(this);
		Terrain *terrainComponent = new Terrain();
		terrain->addComponent(terrainComponent);
		//terrainComponent->createTerrain("Resources/terrain.bmp",500,25);
		terrainComponent->createFractalTerrain(256,500,15,2.0);
		terrain->setMaterial(procmat);
		terrain->getTransform()->setLocalPosition(Vector3(0,-20,0));
		terrain->getTransform()->setParent(root);
		terrain->getTransform()->name = "Terrain";

		//camObj->addComponent(new TerrainFollower(terrainComponent,2.0));
		
		cout << "creating sphere\n";
		GameObject *sphere = new GameObject(this);
		sphere->setMesh(new Sphere(1.0,32));
		sphere->setMaterial(smiley);
		sphere->getTransform()->setLocalPosition(Vector3(15,0,0));		
		sphere->getTransform()->setParent(root);
		sphere->getTransform()->name = "Sphere";

		cout << "creating sphere2 as child\n";
		GameObject *sphere2 = new GameObject(this);
		sphere2->setMesh(new Sphere(1.0,32));
		sphere2->setMaterial(red);
		sphere2->getTransform()->setLocalPosition(Vector3(1,0,0));		
		sphere2->getTransform()->setParent(sphere->getTransform());
		sphere2->getTransform()->name = "Child";

		cout << "creating text \"Hello World\" texture\n";
		Texture *texttex = new Texture(64,64);
		texttex->clear(Colour(255,255,255,255));
		font *f = getFont("resources/FreeSans.ttf", 24);
		if (f != NULL) {
			texttex->writeText(2, 2, "Hello", Colour(0,255,0,255), f->getFont());
			texttex->writeText(0, 30, "World", Colour(255,0,0,0), f->getFont());
		}
		renderer->loadTexture(texttex, true);		
		Material *textmat = renderer->createMaterial(Renderer::PR_OPAQUE);
		textmat->setTexture(texttex,1);

		cout << "creating billboard\n";
		GameObject *billboard = new GameObject(this);
		Billboard *billboardComponent = new Billboard(renderer->camera->gameObject->getTransform(),true);
		billboard->addComponent(billboardComponent);
		billboard->setMaterial(textmat);			// hello world
		billboard->getTransform()->setLocalPosition(Vector3(-10,-3,0));
		billboard->getTransform()->setLocalScale(Vector3(2,2,2));
		billboard->getTransform()->setParent(root);
		billboard->getTransform()->name = "Billboard";

		cout << "creating sweep\n";
		SweepPath sp;
		sp.makeCirclePath(5,32);
		GameObject *sweep = new GameObject(this);
		vector<Vector3> points;
		points.push_back(Vector3(1,0,0));
		points.push_back(Vector3(0.7,0.7,0));
		points.push_back(Vector3(0,1,0));
		points.push_back(Vector3(-0.7,0.7,0));
		points.push_back(Vector3(-1,0,0));
		points.push_back(Vector3(-0.7,-0.7,0));
		points.push_back(Vector3(0,-1,0));
		points.push_back(Vector3(0.7,-0.7,0));
		sweep->setMesh(new Sweep(points,sp,true));
		sweep->setMaterial(red);
		sweep->getTransform()->setLocalPosition(Vector3(0,10,0));
		sweep->getTransform()->setParent(root);
		sweep->getTransform()->name = "Sweep";
		
		cube->addComponent(new LookAtBehaviour(sphere2->getTransform()));

		addTask(new PerfLogTask(this));

		addTask(new DiagMessageTask(this, "Press F9 for help", 2, 32, true, 5.0));

		Animation *anim = new Animation(10.0);
		sphere->addComponent(anim);
		anim->addKey("Child",10.0,Quaternion(),Vector3(1,0,0));
		anim->addKey("Child",0,Quaternion(),Vector3(1,0,0));
		anim->addKey("Child",7.0,Quaternion(),Vector3(3,0,0));
		anim->addKey("Child",5.0,Quaternion(),Vector3(10,0,0));
		anim->addKey("Sphere",10.0,Quaternion(),Vector3(5,0,0));
		anim->addKey("Sphere",0,Quaternion(),Vector3(5,0,0));
		anim->addKey("Sphere",7.0,Quaternion(),Vector3(5,0,10));
		anim->addKey("Sphere",5.0,Quaternion(Vector3(0,0,Math::HALF_PI)),Vector3(5,0,5));
		anim->loop(true);	

		// Demonstrate depth sorting
		// Materials creation order defines normal draw order (drawing is grouped by material)
		// So draw order will be all objects using tgreen followed by all tblue objects
		// Without depth sorting the effect of the blue plane, which is behind front of the green
		// but drawn last will not be seen.
		// Note that both materials are created with PR_TRANSPARENT priority. This will cause them
		// to be drawn after all PR_OPAQUE materials so it is not necessary to use depth sorting
		// unless there are multiple transparent materials that may overlap.
		cout << "creating transparent planes\n";
		Material *tgreen = renderer->createMaterial(Renderer::PR_TRANSPARENT);
		tgreen->setDiffuse(0,1,0,0.4);
		tgreen->setBlending(Material::BLEND_DEFAULT);
		tgreen->setSortedDraw(true, true);
		// a Transparent Plane
		GameObject *plane = new GameObject(this);
		plane->setMesh(new PlaneMesh(1));
		plane->setMaterial(tgreen);
		plane->getTransform()->setLocalPosition(Vector3(1,0,17.1));
		plane->getTransform()->setLocalRotation(Vector3(90*Math::DEG2RAD,0,0));
		plane->getTransform()->setParent(root);
		plane->getTransform()->name = "Transparent Green Plane";
		// transparent blue material
		Material *tblue = renderer->createMaterial(Renderer::PR_TRANSPARENT);
		tblue->setDiffuse(0,0,1,0.4);
		tblue->setBlending(Material::BLEND_DEFAULT);
		tblue->setSortedDraw(true, true);
		// another Transparent Plane
		plane = new GameObject(this);
		plane->setMesh(new PlaneMesh(1));
		plane->setMaterial(tblue);
		plane->getTransform()->setLocalPosition(Vector3(1.3,0,17));
		plane->getTransform()->setLocalRotation(Vector3(90*Math::DEG2RAD,0,0));
		plane->getTransform()->setParent(root);
		plane->getTransform()->name = "Transparent Blue Plane";


		cout << "creating spheres to demo shading\n";
		// Red Smooth Specular highlihts sphere
		sphere = new GameObject(this);
		sphere->setMesh(new Sphere(1.0,32));
		sphere->setMaterial(red);
		sphere->getTransform()->setLocalPosition(Vector3(-4,0,0));		
		sphere->getTransform()->setParent(root);
		sphere->getTransform()->name = "Sphere";
		// Green Flat sphere
		sphere = new GameObject(this);
		sphere->setMesh(new Sphere(1.0,16));
		sphere->setMaterial(green);
		sphere->getTransform()->setLocalPosition(Vector3(-5,0,0));		
		sphere->getTransform()->setParent(root);
		sphere->getTransform()->name = "Sphere";

		cout << "creating particle system\n";

		GameObject *particles = new GameObject(this);
		ParticleEmitter *particleSys = new ParticleEmitter(10.0f, 0.1f, 10.0f, 5.0f, 10.0f, 100.0f, 0.2f);
		particles->setMesh(new Cube(1));
		particles->setMaterial(red);
		particles->addComponent(particleSys);
		particles->getTransform()->setLocalPosition(Vector3(1, 3, 3));
		particles->getTransform()->setParent(root);
		particles->getTransform()->name = "Particle System";

		particleSys->createBillboardParticles(20, 3, 0.4, 1.6, flamemat, 2.0, root);
		particleSys->setPositionRange(3);
		particleSys->setVelocity(Vector3(0,2,0), Vector3(0.5,0.5,0.5));
		particleSys->setAcceleration(Vector3(5,0,0), Vector3(3,0,0));

		// Manually add particles
		/*for (int i=0; i<20; i++)
		{
			GameObject *particle = new GameObject(this);
			Billboard *bbComponent = new Billboard(renderer->camera->gameObject->getTransform(),true);
			particle->addComponent(bbComponent);
			ParticleBehaviour *behaviour = new ParticleBehaviour(particleSys, 0.4, 1.6);
			particle->addComponent(behaviour);
			behaviour->setPositionRange(3);
			behaviour->setVelocity(Vector3(0,2,0), Vector3(0.5,0.5,0.5));
			behaviour->setAcceleration(Vector3(5,0,0), Vector3(3,0,0));

			particle->setMaterial(flamemat);			// hello world
			particle->getTransform()->setLocalScale(Vector3(2,2,2));
			particle->getTransform()->setParent(root);
			particle->getTransform()->name = "partice";

			particleSys->addParticle(behaviour, false);
		}
		*/

				// simple flat plane for texture demo
		/*GameObject *plane = new GameObject(this);
		plane->setMesh(new PlaneMesh(1));
		plane->setMaterial(flamemat);
		plane->getTransform()->setLocalPosition(Vector3(3,0,0));
		plane->getTransform()->setLocalRotation(Vector3(90*Math::DEG2RAD,0,0));
		plane->getTransform()->setParent(root);
		plane->getTransform()->name = "Plane";	*/


		/*
		Animation *b = new Animation(10,5);
		cube->addComponent(b);
		b->addKey("Cube",9,Quaternion(),Vector3(0,0,0));
		b->addKey("Cube",0,Quaternion(),Vector3(0,0,0));
		b->addKey("Cube",3,Quaternion(Vector3(Math::HALF_PI,0,Math::HALF_PI)),Vector3(0,0,0));
		b->addKey("Cube",7,Quaternion(Vector3(0,Math::HALF_PI,0)),Vector3(0,0,0));
		b->addKey("Cube",5,Quaternion(Vector3(0,-Math::HALF_PI,0)),Vector3(0,0,0));
		b->loop(true);
		b->interpolate();	
		*/

		return true;
	}
}