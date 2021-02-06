// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// winglapplication.h
//
// t3d application for windows and OpenGL

#include <gl/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <sdl\SDL_ttf.h>

#include "WinGLApplication.h"

#include "DefaultDebugOptions.h"
#include "GLRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Input.h"
#include "PerfLogTask.h"
#include "DiagMessageTask.h"
#include "SoundManager.h"
#include "Logger.h"


// stdin, stdout, and stderr are defined differently in Visual Studio 2015
// This is required to give backward combatibility with the version of SDL being used.
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}



namespace T3D 
{

	WinGLApplication::WinGLApplication(void)
	{
		surf = NULL;
		running = false;
		renderer = new GLRenderer();		
		root = new Transform(NULL,"Root");
	}


	WinGLApplication::~WinGLApplication(void)
	{
		delete root;
		root = NULL;
		delete renderer;
		renderer = NULL;
	}

	bool WinGLApplication::init(){
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			return false;
		}

		//Load from DefaultDebugOptions
		if (DefaultDebugOptions::showWireframe)
			renderer->toggleWireframe();
		if (DefaultDebugOptions::showAxes)
			renderer->toggleAxes();
		if (DefaultDebugOptions::showGrid)
			renderer->toggleGrid();
		if (DefaultDebugOptions::showVertices)
			renderer->togglePoints();

		/* Logger Initialization */
		{
		 /* All categories are disabled by default, e.g. Video, Animation, Platform, Audio and so on. 
			You may not care about all of them, but if a different system needs debugging such as
			music, loading textures, etc, you can enable all of them at once here (or individually as below). 

			As a rule of thumb for priorities stick with "Info" for 'everyday' diagnostics, init messages and 
			codepaths that aren't hit inside the game loop except for objects that are created once 
			and/or static initializers/managers that live for the Applications lifetime , such as DrawTasks.
			*/

			logger::Initialise(priority::Tracing, output_stream::All, true);
			//logger::DisableCategory(category::Task);
			logger::Log(priority::Info, output_stream::All, category::Platform, "T3D Initialized\n");
			
		}

		//Initialize SDL_mixer
		soundManager->init();

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

		if((surf = SDL_SetVideoMode(renderer->WindowWidth, renderer->WindowHeight, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
			return false;
			SDL_Quit();
		}
		glewInit();
		glClearColor(0, 0, 0, 0);
		glClearDepth(1.0f);
		glViewport(0, 0, renderer->WindowWidth, renderer->WindowHeight);

		// Initialize SDL_ttf library
		if (TTF_Init() != 0)
		{
			logger::Log(priority::Error, output_stream::All, category::Platform, "TTF_Init() Failed: %s\n", TTF_GetError());
			SDL_Quit();
			exit(1);
		}

		SDL_WM_GrabInput(SDL_GRAB_ON);

		SDL_ShowCursor(SDL_DISABLE);

		logger::Log(priority::Tracing, output_stream::File, category::Platform, "%s", glGetString(GL_VERSION));

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
			soundManager->update();

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
	}

	void WinGLApplication::handleEvent(SDL_Event *e){
		switch (e->type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:				
				Input::onKeyDown(e->key.keysym.sym);
				if (Input::keysDown[KEY_ESCAPE])
					running = false;
				if (Input::keysDown[KEY_F1])
					renderer->toggleWireframe();
				if (Input::keysDown[KEY_F2])
					renderer->toggleAxes();
				if (Input::keysDown[KEY_F3])
					renderer->toggleGrid();
				if (Input::keysDown[KEY_F4])
					renderer->togglePoints();
				if (Input::keysDown[KEY_F9])
				{
					int line = 0;
					addTask(new DiagMessageTask(this, "ESCAPE     quit", 2, 600-(line++*20), true, 5.0));
					addTask(new DiagMessageTask(this, "F1         wireframe", 2, 600-(line++*20), true, 5.0));
					addTask(new DiagMessageTask(this, "F2         axes", 2, 600-(line++*20), true, 5.0));
					addTask(new DiagMessageTask(this, "F3         grid", 2, 600 - (line++ * 20), true, 5.0));
					addTask(new DiagMessageTask(this, "F4         points", 2, 600 - (line++ * 20), true, 5.0));
					addTask(new DiagMessageTask(this, "F9         show help", 2, 600-(line++*20), true, 5.0));
					addTask(new DiagMessageTask(this, "F10        show stats", 2, 600-(line++*20), true, 5.0));
				}
				if (Input::keysDown[KEY_F10])
				{
					// find log task
					PerfLogTask *task = (PerfLogTask *)findTask("PerfLogTask");
					if (task)
					{
						// toggle on screen diagnostics
						task->setDiagDisplay(!task->getDiagDisplay());
					}
				}
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
