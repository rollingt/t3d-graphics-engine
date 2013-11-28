// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// gameobject.cpp
//
// Everything that exists in the scene has a corresponding GameObject
// Alter functionality by attaching components
// Position in scene is defined by Transform

#include "GameObject.h"
#include "T3DApplication.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "Terrain.h"

namespace T3D
{
	GameObject::GameObject(T3DApplication *app)
	{
		this->app = app;
		setTransform(new Transform());
		camera = NULL;
		mesh = NULL;
		material = NULL;
		light = NULL;
	}


	GameObject::~GameObject(void)
	{
		if (camera) delete camera;
		if (mesh) delete mesh;
		if (light) delete light; // TODO: should make sure that this is removed from renderer's list of lights

		// don't delete transform - normally gameobject delete will be called from transform delete
	}

	void GameObject::setTransform(Transform *t){
		transform = t;
		t->gameObject = this;
	}
	Transform* GameObject::getTransform(){
		return transform;
	}	
	
	void GameObject::setCamera(Camera *c){
		camera = c;
		camera->gameObject = this;
	}

	Camera* GameObject::getCamera(){
		return camera;
	}
	
	void GameObject::setLight(Light *l){
		light = l;
		light->gameObject = this;
		app->getRenderer()->lights.push_back(light);
	}

	Light* GameObject::getLight(){
		return light;
	}
	
	void GameObject::setMaterial(Material *m){
		material = m;
	}

	Material* GameObject::getMaterial(){
		return material;
	}
	
	void GameObject::setMesh(Mesh *m){
		mesh = m;
		mesh->gameObject = this;
	}
	Mesh* GameObject::getMesh(){
		return mesh;
	}	

	void GameObject::addComponent(Component *component){
		components.push_back(component);
		component->init(this);
	}

	void GameObject::update(float dt){
		std::vector<Component*>::iterator it;

		for ( it=components.begin() ; it < components.end(); it++ )
		{
			(*it)->update(dt);
		}
	}
}
