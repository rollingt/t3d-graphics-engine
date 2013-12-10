// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// perflogtask.cpp
//
// Simple class to track framerates and write to file when app closes

#include <sstream>
#include <fstream>
#include "perflogtask.h"

namespace T3D{

	PerfLogTask::PerfLogTask(T3DApplication *app) : Task(app)
	{		
		setName("PerfLogTask");

		frameCount = 0;
		elapsedTime = 0;
		dtmin = 1000; //close enough
		dtmax = 0;

		diagDisplay = false;
		diagOverlay = NULL;
	}


	PerfLogTask::~PerfLogTask(void)
	{
		log();
	}

	void PerfLogTask::log(){		
		std::ofstream logfile;
		logfile.open ("perflog.txt");
		logfile << "frames: " << frameCount << "\n";
		logfile << "elapsed time: " << elapsedTime << "\n";
		logfile << "frame rate (min/avg/max): " << 1.0/dtmax << "/" << frameCount/elapsedTime << "/" << 1.0/dtmin << "\n";
		logfile.close();
	}

	void PerfLogTask::update(float dt){
		frameCount++;
		elapsedTime += dt;
		if (dt<dtmin) dtmin = dt;
		if (dt>dtmax) dtmax = dt;

		//if (frameCount>0 && frameCount%100 == 0) log();

		if ((frameCount % 15) == 0)			// update every quarter second
		{
			if (diagOverlay)
			{
				app->getRenderer()->remove2DOverlay(diagOverlay);
				app->getRenderer()->unloadTexture(diagOverlay->getID());
				delete diagOverlay;
				diagOverlay = NULL;
			}

			if (diagDisplay)
			{
				font *f = app->getFont("resources/FreeSans.ttf", 16);
				if (f != NULL)
				{
					std::ostringstream ss;
					ss << "frames: " << frameCount;
					ss << ", elapsed time: " << elapsedTime;
					ss << ", frame rate (min/avg/max): " << 1.0/dtmax << "/" << frameCount/elapsedTime << "/" << 1.0/dtmin;

					int w = 1024;		// texture width, should be large enough for most diagnostics
					int h = 32;			// should be enough for single line (text wrap is not supported)
					diagOverlay = new Texture(w,h);
					diagOverlay->clear(Colour(0,0,0,255));
					diagOverlay->writeText(0, 0, ss.str().c_str(), Colour(255,255,255,255), f->getFont());
					app->getRenderer()->loadTexture(diagOverlay, false);

					app->getRenderer()->add2DOverlay(diagOverlay, 0, 0);
				}
			}
		}
	}

}