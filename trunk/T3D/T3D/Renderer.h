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

	class Renderer
	{
	public:
		Renderer(void);
		virtual ~Renderer(void);

		virtual void prerender() = 0;
		virtual void render(Transform *root);
		virtual void postrender() = 0;

		virtual void draw(GameObject *object) = 0;

		virtual void loadTexture(Texture *tex, bool repeat = false) = 0;	// returns texture id
		virtual void unloadTexture(unsigned int textureID) = 0;				// unload from GL

		virtual void loadSkybox(std::string tex) = 0; 

		virtual void add2DOverlay(Texture *texture, int x, int y) = 0;	// 2D overlay (used for on screen diagnostic messages mainly)
		virtual void remove2DOverlay(Texture *texture) = 0;				// remove overlay
		
		void setFog(float d, float r, float g, float b, float a);
		void toggleFog(){ showFog = !showFog; }
		void toggleWireframe(){ showWireframe = !showWireframe; }
		void toggleGrid(){ showGrid = !showGrid; }
		void toggleAxes(){ showAxes = !showAxes; }

	private:		
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
	};
}

#endif