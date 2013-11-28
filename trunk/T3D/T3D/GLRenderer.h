// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// glrenderer.h
//
// Handles rendering tasks using OpenGL

#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "renderer.h"

namespace T3D
{
	class GLRenderer :
		public Renderer
	{
	public:
		GLRenderer(void);
		virtual ~GLRenderer(void);

		void prerender();
		void postrender();

		void draw(GameObject* object);
		
		virtual void loadTexture(Texture *tex, bool repeat = false); // returns texture id
		virtual void loadSkybox(std::string tex);

	private:
		void drawMesh(Mesh *mesh);
		void drawSkybox();
	};
}

#endif
