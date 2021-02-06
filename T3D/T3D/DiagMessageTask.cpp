// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// DiagMessageTask.h
//
// Onscreen diagnostic/debug messages

#include <algorithm> // std::max

#include "DiagMessageTask.h"
#include "Colour.h"
#include "Texture.h"
#include "Logger.h"
#include "Renderer.h"
#include "GLRenderer.h"
#include "Font.h"

namespace T3D {

	/*
	 * \param app Application root
	 */
	DiagMessageTask::DiagMessageTask(T3DApplication *app) : Task(app)
	{		
		setName("DiagMessageTask");
		refresh     = false;
		timed       = false;
		diagOverlay = NULL;
		logger::Log(priority::Info, output_stream::All, category::Task, "Initialised persistent DiagMessageTask");
	}

	/*
	 * \param Application root
	 * \param message text to display, assumed null-terminated c-string (i.e. what std::string::c_str() provides)
	 * \param x Leftmost x coordinate the message shall start, in pixels.
	 * \param x Upper y coordinate the message shall start, in pixels. Note that `y_max` is at the top of the screen
	 * \param timed Does the message have a duration?
	 * \param duration Duration in seconds
	 */
	DiagMessageTask::DiagMessageTask(T3DApplication *app, const char *message, int x, int y, bool timed, float duration) : Task(app)
	{		
		setName("DiagMessageTask");

		this->timed = timed;
		time = duration;

		setMessage(message, x, y);

		diagOverlay = NULL;
		logger::Log(priority::Tracing, output_stream::All, category::Task, "Initialised timed DiagMessageTask");
	}

	DiagMessageTask::~DiagMessageTask(void)
	{
		removeOverlay();
		logger::Log(priority::Tracing, output_stream::All, category::Task, "End DiagMessageTask");
	}

	/*
	 * \param dt Change in time
	 * \note If this function is not working, it's probably a font error, but it could also be a hard-coded screen coordinate. Check `T3D_Log.txt`.
	 */
	void DiagMessageTask::update(float dt){
		if (timed)
		{
			time -= dt;
			if (time < 0.0f) setFinished(true);
		}

		if (refresh)
		{
			removeOverlay();

			font *f = app->getFont("Resources/FreeSans.ttf", 16);
			if (f)
			{
				if (!diagOverlay) {
					// Create and add overlay
					int w = app->getRenderer()->WindowWidth; // texture width, should be large enough for most diagnostics
					int h = 32;	// should be enough for single line (text wrap is not supported)

					diagOverlay = new Texture(w,h);

					diagOverlay->clear(Colour(0,0,0,255));
					diagOverlay->writeText(0, 0, message.c_str(), Colour(255,255,255,255), f->getFont());
					app->getRenderer()->loadTexture(diagOverlay, false);			// load new texture in renderer
					app->getRenderer()->add2DOverlay(diagOverlay, x, y);			// add to renderer overlays

					logger::Log(priority::Tracing, 
								output_stream::File, 
								category::Task, 
								"Created overlay for DiagMessageTask");
				}
				else 
				{
					// refresh overlay
					diagOverlay->clear(Colour(0,0,0,255));
					diagOverlay->writeText(0, 0, message.c_str(), Colour(255,255,255,255), f->getFont());
					app->getRenderer()->reloadTexture(diagOverlay);					// reload texture in renderer
				}
			}
		}

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

	/*
	 * \param message new text to display. Assumed null-terminated c-string.
	 * \param x new x coordinate
	 * \param y new y coordinate. Note that 'Y_max' is the top of the screen in T3D.
	 */
	void DiagMessageTask::setMessage(const char *message, int x, int y){
		this->message = message;
		this->x = x;
		this->y = y;
		refresh = true;
	}

	/*
	 * \param duration New duration
	 */
	void DiagMessageTask::setTimed(float duration)
	{
		timed = true;
		time = duration;
	}

}
