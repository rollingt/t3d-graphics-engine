// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// winglapplication.h
//
// t3d application for windows and OpenGL

#include <windows.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include "WinGLApplication.h"
#include "GLRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Input.h"

namespace T3D 
{

	WinGLApplication::WinGLApplication(void)
	{
		surf = NULL;
		running = false;
		renderer = new GLRenderer();		
		root = new Transform();
	}


	WinGLApplication::~WinGLApplication(void)
	{
		delete root;
		delete renderer;
	}

	bool WinGLApplication::init(){
		cout << "init\n";
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

		if((surf = SDL_SetVideoMode(1024, 640, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
			return false;
		}
		glewInit();
		glClearColor(0, 0, 0, 0);
		glClearDepth(1.0f);
		glViewport(0, 0, 1024, 640);

		// TODO: Fix this so that camera projection is used (probably move to pre-render)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,1.6,0.1,500);

		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_TEXTURE_2D);

		glLoadIdentity();

		SDL_WM_GrabInput(SDL_GRAB_ON);

		SDL_ShowCursor(SDL_DISABLE);

		return true;
	}
		
	int WinGLApplication::run(void){		
		if(init() == false) {
			return -1;
		}
		running = true;

		SDL_Event sdlEvent;
		lastFrame = SDL_GetTicks()/1000.0f;
		while(running) {
			float thisFrame = SDL_GetTicks()/1000.0f;
			dt = thisFrame-lastFrame;
			lastFrame = thisFrame;
			
			Input::onMouseMotion(0,0);
			while(SDL_PollEvent(&sdlEvent)) {
				handleEvent(&sdlEvent);
			}

			updateTasks();

			updateComponents(root);

			renderer->prerender();
			renderer->render(root);
			renderer->postrender();
		}

		quit();

		return 0;
	}

	void WinGLApplication::quit(void){	
		SDL_Quit();
	}

	void WinGLApplication::handleEvent(SDL_Event *e){
		switch (e->type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:				
				Input::onKeyDown(e->key.keysym.sym);
				if (Input::keyDown[KEY_ESCAPE])
					running = false;
				break;
			case SDL_KEYUP:
				Input::onKeyUp(e->key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				Input::onMouseMotion((e->motion).xrel,(e->motion).yrel);
				break;
		}
	}

}
