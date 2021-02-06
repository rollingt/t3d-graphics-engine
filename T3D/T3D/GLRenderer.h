// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// glrenderer.h
//
// Handles rendering tasks using OpenGL
#pragma once

#include <list>
#include "Renderer.h"

namespace T3D
{
	// Entry for simple display of text on screen. This is intended for diagnostic type display only
	// Messages are only displayed for current frame then deleted
	// This would be better implemented as a proper GameObject within the scene but there is currently
	// no way to manage a 2D rendering context.
	typedef struct {
		Texture *texture;
		int x,y;					// screen/window coordinates. NOTE(Evan): X increases left-to-right, Y increases up-to-down.
	} overlay2D;


	//! \brief OpenGL renderer. Manages 2D overlays, skyboxes, materials and renders meshes.
	class GLRenderer :
		public Renderer
	{
	public:
		//! \brief Create GLRenderer (trivially).
		GLRenderer(void)          = default;

		//! \brief Destroy GLRenderer (trivially).
		virtual ~GLRenderer(void) = default;

		//! \brief Setup OpenGL state, such as clearing depth, colour and stencil buffers.
		void prerender();

		//! \brief Post-render hooks such as 2D overlays using orthographic projection.
		void postrender();

		//! \brief Set Camera to render scene from perspective of.
		void setCamera(Camera *cam);

		//! \brief Draw an Object's Mesh with respect to Material and Transform.
		void draw(GameObject* object);
		
		//! \brief Register the Texture with OpenGL, setting its ID.
		void loadTexture(Texture *tex, bool repeat = false);

		//! \brief Reload the Texture. Does not retain the same ID.
		void reloadTexture(Texture *tex);

		//! \brief Unload the Texture from OpenGL.
		void unloadTexture(Texture *tex);

		//! \brief Load 6 faces of a Skybox bitmap from path.
		void loadSkybox(std::string tex);

		bool exists2DOverlay(Texture *texture);					// is there a existing 2D overlay using this texture?
		void add2DOverlay(Texture *texture, int x, int y);		// 2D overlay (used for on screen diagnostic messages mainly)
		void remove2DOverlay(Texture *texture);					// remove overlay

	private:
		void loadMaterial(Material* mat);
		void unloadMaterial(Material* mat);

		int GLRenderer::getTextureFormat(Texture *tex);

		void drawMesh(Mesh *mesh);
		void drawSkybox();

		void showD2DOverlays();
		void drawText();
		void draw2DMesh(overlay2D *overlay);

		std::list<overlay2D *> overlays;

	};
}
