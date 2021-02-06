// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// winglapplication.h
//
// t3d application for windows and OpenGL
#pragma once

#include <sdl\SDL.h>

#include "T3DApplication.h"
#include "FontCache.h"

namespace T3D 
{
	//! \brief Application driver using Win32, OpenGL 1.x and SDL.
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
