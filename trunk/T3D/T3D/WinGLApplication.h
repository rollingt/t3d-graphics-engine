// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// winglapplication.h
//
// t3d application for windows and OpenGL

#ifndef WINGLAPPLICATION_H
#define WINGLAPPLICATION_H

#include <sdl\SDL.h>

#include "t3dapplication.h"
#include "FontCache.h"

namespace T3D 
{

	class WinGLApplication :
		public T3DApplication
	{
	protected:
		SDL_Surface *surf;
		FontCache fonts;

	public:
		WinGLApplication(void);
		virtual ~WinGLApplication(void);

		bool init();		
		int run(void);
		void quit(void);

		void handleEvent(SDL_Event *e);

		font *getFont(const char *filename, int pointSize) { return fonts.getFont(filename, pointSize); }

	};

}

#endif

