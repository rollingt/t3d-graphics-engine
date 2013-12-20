// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// renderer.cpp
//
// Abstract base class for all rendering operations
// Recursively draws all objects in scene graph

#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Cube.h"

namespace T3D
{
	/*! Constructor
	  Initialises members
	  */
	Renderer::Renderer(void)
	{
		camera = NULL;
		renderSkybox = false;

		showFog = false;
		fogDensity = 0;
		fogColour[0] = 0;
		fogColour[1] = 0;
		fogColour[2] = 0;
		fogColour[3] = 1;
		ambient[0] = 0.1;
		ambient[1] = 0.1;
		ambient[2] = 0.1;
		ambient[3] = 1;

		showWireframe = false;
		showGrid = false;
		showAxes = false;
	}

	/*! Destructor
	  The destructor is responsible for freeing all components
	  \todo		Free materials and check for other stuff that might need freeing
	  */
	Renderer::~Renderer(void)
	{
	}

	/*! Sets the fog colour and density
	  \param d	The new density
	  \param r	The new red compontent
	  \param g	The new green compontent
	  \param b	The new blue compontent
	  \param a	The new alpha compontent
	  */
	void Renderer::setFog(float d, float r, float g, float b, float a){ 
		fogDensity = d; 
		fogColour[0] =r; 
		fogColour[1] = g; 
		fogColour[2] = b; 
		fogColour[3] = a; 
	}

	/*! Creates a material and adds it to the priority list
	  GameObjects are sorted by material before being rendered.  The order of rendering is determined by the material priority
	  \param param	The priority for this material
	  */
	Material* Renderer::createMaterial(int priority){
		Material* m = new Material();
		materials[priority].push_back(m);
		return m;
	}

	/*! Renders the scenegraph
	  This method is responsible for sorting by material and rendering game objects in material priority order
	  \param root	The root of the scenegraph to be rendered
	  */
	void Renderer::render(Transform *root){
		std::vector<Material*>::iterator mit;
		std::vector<GameObject*>::iterator goit;
		for (int i=0; i<PRIORITY_LEVELS; i++){
			for (mit = materials[i].begin(); mit!=materials[i].end(); mit++){
				(*mit)->clearQueue();
			}
		}

		buildRenderQueue(root);

		for (int i=0; i<PRIORITY_LEVELS; i++){
			for (mit = materials[i].begin(); mit!=materials[i].end(); mit++){
				loadMaterial(*mit);
				std::vector<GameObject*> q = (*mit)->getQueue();
				for (goit = q.begin(); goit != q.end(); goit++){
					draw(*goit);
				}
			}
		}

	}

	/*! Sorts game objects by material
	  This method traverses the scenegraph and adds game objects their respective material's render queues
	  \param root	The root of the scenegraph to be sorted
	  */
	void Renderer::buildRenderQueue(Transform *root){
		if (root->gameObject) {
			Material* m = root->gameObject->getMaterial();
			if (m) m->addToQueue(root->gameObject);
		}

		if(!root->children.empty())
		{
			for(int i = 0; i < root->children.size(); ++i)
			{
				if(NULL != root->children[i])
				{
					buildRenderQueue(root->children[i]);
				}
			}
		}
	}
}
