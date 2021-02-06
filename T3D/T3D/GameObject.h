// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.h
//
// Class to manage all information relating to objects in the scene.  Includes link to Transform and all Components
#pragma once

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

	//! Generic class for all objects that exist in the world
	/*! 
	 * A GameObject's location is defined by the attached Transform.  
	 * The behaviour of a GameObject is customised by adding one or more Component's.  
	 * Special Component's such as Light's, Camera's and Material's, should be added using the appropriate method.
	 * 
	 * \note A common mistake is to not add the attached Transform component to the root of the scene graph. See T3DTest for an example.
	 * \note The order which Components are updated is based on the order they are added / deleted - beware of issues with multiple Transform-modifying components!
	 * \author  Robert Ollington
	 */
	class GameObject
	{
	public:
		//! \brief Create a GameObject associated with a T3DApplication
		GameObject(T3DApplication *app);

		//! \brief Destroy a GameObject and its components
		~GameObject(void);

		//! \brief Attach Transform component
		void setTransform(Transform *t);

		//! \brief Get Transform component
		Transform* getTransform();
		
		//! \brief Attach Camera component
		//! \note Use `setCamera` on the Renderer to draw the scene from the perspective of the GameObject
		void setCamera(Camera *s);

		//! \brief Get Camera component
		Camera* getCamera();
		
		//! \brief Attach Light component
		void setLight(Light *l);

		//! \brief Get Light component
		Light* getLight();

		//! \brief Attach Material component
		void setMaterial(Material *m);

		//! \brief Get Material component
		Material* getMaterial();
		
		//! \brief Attach Mesh component
		void setMesh(Mesh *m);

		//! \brief Get Mesh component
		Mesh* getMesh();

		//! \brief Return Application root; useful for obtaining Renderer handle.
		T3DApplication *getApp() { return app; }

		//! \brief Add a Component to the GameObject.
		//! \note For Components such as `Mesh`, `Light`, `Material` etc, use the dedicated functions.
		void addComponent(Component *component);

		//! \brief Update the GameObject and all its components.
		void update(float dt);

		//! \brief Set distance to Camera. Used for sorted draw order.
		void setDistanceToCamera(float distance) { distanceToCamera = distance; }

		//! \brief Get distance to Camera. Used for sorted draw order.
		float getDistanceToCamera() const        { return distanceToCamera; }

		//! \brief Set rendering visibility. 
		void setVisible(bool visible) { this->visible = visible; }

		//! \brief Query rendering visibility.
		bool isVisible()              { return visible; }

		//! \brief Set alpha override.
		//! \note This will override the GameObject's Material if < 1.0
		void setAlpha(float alpha) { this->alpha = alpha; }
		float getAlpha()           { return alpha; }

	protected:
		//! \brief Application root. Provides handle to Renderer.
		T3DApplication *app;

		//! \brief Transform position in the scene graph.
		Transform  *transform;

		//! \brief Camera object associated with a scene.
		Camera *camera;

		//! \brief Light associated with GameObject.
		Light *light;

		//! \brief Material associated with GameObject.
		Material *material;

		//! \brief Mesh associated with GameObject.
		Mesh *mesh;

		//! \brief Material alpha; override is < 1.0f
		float alpha;

	private:		
		//! \brief Container of Components this GameObject has.
		std::vector<Component*> components;

		//! \brief Will GameObject be drawn or not
		bool visible;

		//! \brief Temporary valued used for sorted draw order only.
		float distanceToCamera;

	};
}

