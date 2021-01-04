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
	#define WINDOW_WIDTH		1024
	#define	WINDOW_HEIGHT		640

	// Width of the window provided by the OS layer, in pixels.
	const uint32_t WindowWidth = WINDOW_WIDTH;
	// Height of the window provided by the OS layer, in pixels.
	const uint32_t WindowHeight = WINDOW_HEIGHT;

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
		
		virtual void draw(GameObject *object) = 0;

		virtual void loadTexture(Texture *tex, bool repeat = false) = 0;	// load Texture into GL
		virtual void reloadTexture(Texture *tex) = 0;						// reload previously loaded Texture (refresh)
		virtual void unloadTexture(Texture *tex) = 0;						// unload Texture from GL

		virtual void loadSkybox(std::string tex) = 0; 

		virtual bool exists2DOverlay(Texture *texture) = 0;					// is there a existing 2D overlay using this texture?
		virtual void add2DOverlay(Texture *texture, int x, int y) = 0;		// 2D overlay (used for on screen diagnostic messages mainly)
		virtual void remove2DOverlay(Texture *texture) = 0;					// remove overlay

		virtual Material* createMaterial(int priority); // creates a material and returns a pointer to it
		
		void setFog(float d, float r, float g, float b, float a);
		void toggleFog(){ showFog = !showFog; }
		void toggleWireframe(){ showWireframe = !showWireframe; }
		void togglePoints(){ showPoints = !showPoints; }
		void toggleGrid(){ showGrid = !showGrid; }
		void toggleAxes(){ showAxes = !showAxes; }

	private:	
		virtual void buildRenderQueue(Transform *root);
		virtual void loadMaterial(Material *mat) = 0;
		virtual void unloadMaterial(Material *mat) = 0;

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

		bool showWireframe, showPoints, showGrid, showAxes;

	private:
		std::vector<Material*> materials[PRIORITY_LEVELS];
	};
}

#endif