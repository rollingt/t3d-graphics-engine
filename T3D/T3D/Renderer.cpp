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
	}


	Renderer::~Renderer(void)
	{
	}

	void Renderer::setFog(float d, float r, float g, float b, float a){ 
		fogDensity = d; 
		fogColour[0] =r; 
		fogColour[1] = b; 
		fogColour[2] = b; 
		fogColour[3] = a; 
	}

	void Renderer::render(Transform *root){
		if (root->gameObject) {
			draw(root->gameObject);
		}

		if(!root->children.empty())
		{
			for(int i = 0; i < root->children.size(); ++i)
			{
				if(NULL != root->children[i])
				{
					render(root->children[i]);
				}
			}
		}
	}
}
