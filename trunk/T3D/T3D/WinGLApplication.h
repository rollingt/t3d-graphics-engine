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

namespace T3D 
{

	class WinGLApplication :
		public T3DApplication
	{
	private:
		SDL_Surface *surf;

	public:
		WinGLApplication(void);
		virtual ~WinGLApplication(void);

		bool init();		
		int run(void);
		void quit(void);

		void handleEvent(SDL_Event *e);
	};

}

#endif

