// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// gameobject.h
//
// Everything that exists in the scene has a corresponding GameObject
// Alter functionality by attaching components
// Position in scene is defined by Transform

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Mesh.h"
#include "Material.h"

namespace T3D
{
	class T3DApplication;
	class Transform;
	class Component;
	class Camera;
	class Light;

	class GameObject
	{
	public:
		GameObject(T3DApplication *app);
		~GameObject(void);

		void setTransform(Transform *t);
		Transform* getTransform();
		
		void setCamera(Camera *s);
		Camera* getCamera();
		
		void setLight(Light *l);
		Light* getLight();

		void setMaterial(Material *m);
		Material* getMaterial();
		
		void setMesh(Mesh *m);
		Mesh* getMesh();

		T3DApplication* getApp(){return app; }

		void addComponent(Component *component);
		void update(float dt);

	protected:
		T3DApplication *app;
		Transform* transform;
		Camera* camera;
		Light* light;
		Material* material;
		Mesh* mesh;

	private:		
		std::vector<Component*> components;
	};
}

#endif