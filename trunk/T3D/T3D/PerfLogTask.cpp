// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// perflogtask.cpp
//
// Simple class to track framerates and write to file when app closes

#include <fstream>
#include "perflogtask.h"

namespace T3D{

	PerfLogTask::PerfLogTask(void)
	{		
		frameCount = 0;
		elapsedTime = 0;
		dtmin = 1000; //close enough
		dtmax = 0;
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
	}

}