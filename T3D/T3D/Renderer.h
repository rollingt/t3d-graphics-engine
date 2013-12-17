// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// renderer.h
//
// Abstract base class for all rendering operations

#ifndef RENDERER_H
#define RENDERER_H

#include "Transform.h"
#include "GameObject.h"
#include "Light.h"
#include "Mesh.h"
#include "Texture.h"

namespace T3D
{
	class Camera;

	//! Generic class for renderers
	/*! The render is responsible for managing materials and drawing meshes
	  \author  Robert Ollington
	  */
	class Renderer
	{
	public:
		static const int PR_SKYBOX = 0;			//! Priority level for skybox (drawn first)
		static const int PR_TERRAIN = 2;		//! Priority level for terrain
		static const int PR_OPAQUE = 4;			//! Priority level for standard opaque meshes
		static const int PR_TRANSPARENT = 6;	//! Priority level for transparent meshes
		static const int PR_OVERLAY = 8;		//! Priority level for overlays (drawn last)
		static const int PRIORITY_LEVELS = 10; 


		Renderer(void);
		virtual ~Renderer(void);

		virtual void prerender() = 0;
		virtual void render(Transform *root);
		virtual void postrender() = 0;
		
		virtual void setRenderContext(int renderPriority) = 0;				// set render context corresponding to PR_??? priority level
		virtual void draw(GameObject *object) = 0;

		virtual void loadTexture(Texture *tex, bool repeat = false) = 0;	// returns texture id
		virtual void unloadTexture(unsigned int textureID) = 0;				// unload from GL

		virtual void loadSkybox(std::string tex) = 0; 

		virtual void add2DOverlay(Texture *texture, int x, int y) = 0;	// 2D overlay (used for on screen diagnostic messages mainly)
		virtual void remove2DOverlay(Texture *texture) = 0;				// remove overlay

		virtual Material* createMaterial(int priority); // creates a material and returns a pointer to it
		
		void setFog(float d, float r, float g, float b, float a);
		void toggleFog(){ showFog = !showFog; }
		void toggleWireframe(){ showWireframe = !showWireframe; }
		void toggleGrid(){ showGrid = !showGrid; }
		void toggleAxes(){ showAxes = !showAxes; }

	private:	
		virtual void buildRenderQueue(Transform *root);
		virtual void loadMaterial(Material *mat) = 0;

		virtual void drawMesh(Mesh *mesh) = 0;
		virtual void drawSkybox() = 0;
		
	public:
		Camera *camera;
		std::vector<Light*> lights;
		float ambient[4];

		bool renderSkybox;
		Texture *skyboxup, *skyboxdown, *skyboxleft, *skyboxright, *skyboxfront, *skyboxback; 

		bool showFog;
		float fogDensity;
		float fogColour[4];

		bool showWireframe,showGrid,showAxes;

	private:
		std::vector<Material*> materials[PRIORITY_LEVELS];
	};
}

#endif