// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// DiagMessageTask.h
//
// Onscreen diagnostic/debug messages

#include <sstream>
#include <fstream>
#include "DiagMessageTask.h"

namespace T3D{

	DiagMessageTask::DiagMessageTask(T3DApplication *app) : Task(app)
	{		
		setName("DiagMessageTask");
		refresh = false;

		this->timed = false;

		diagOverlay = NULL;
	}

	DiagMessageTask::DiagMessageTask(T3DApplication *app, const char *message, int x, int y, bool timed, float duration) : Task(app)
	{		
		setName("DiagMessageTask");

		this->timed = timed;
		this->time = duration;

		setMessage(message, x, y);

		diagOverlay = NULL;
	}


	DiagMessageTask::~DiagMessageTask(void)
	{
		removeOverlay();
	}

	void DiagMessageTask::removeOverlay()
	{
		if (diagOverlay)
		{
			if (app->getRenderer())		// won't be valid if program exiting
			{
				app->getRenderer()->remove2DOverlay(diagOverlay);
				app->getRenderer()->unloadTexture(diagOverlay);
			}
			delete diagOverlay;
			diagOverlay = NULL;
		}
	}

	void DiagMessageTask::setMessage(const char *message, int x, int y){
		this->message = message;
		this->x = x;
		this->y = y;
		refresh = true;
	}

	void DiagMessageTask::setTimed(float duration)
	{
		timed = true;
		time = duration;
	}

	void DiagMessageTask::update(float dt){
		if (timed)
		{
			time -= dt;
			if (time < 0.0f)
				setFinished(true);
		}

		if (refresh)
		{

			removeOverlay();

			font *f = app->getFont("resources/FreeSans.ttf", 16);
			if (f != NULL)
			{
				if (diagOverlay == NULL) {
					// Create and add overlay
					int w = 1024;		// texture width, should be large enough for most diagnostics
					int h = 32;			// should be enough for single line (text wrap is not supported)
					diagOverlay = new Texture(w,h);

					diagOverlay->clear(Colour(0,0,0,255));
					diagOverlay->writeText(0, 0, message.c_str(), Colour(255,255,255,255), f->getFont());
					app->getRenderer()->loadTexture(diagOverlay, false);			// load new texture in renderer
					app->getRenderer()->add2DOverlay(diagOverlay, x, y);			// add to renderer overlays
				}
				else {
					// refresh overlay
					diagOverlay->clear(Colour(0,0,0,255));
					diagOverlay->writeText(0, 0, message.c_str(), Colour(255,255,255,255), f->getFont());
					app->getRenderer()->reloadTexture(diagOverlay);					// reload texture in renderer
				}
			}
		}

	}

}
