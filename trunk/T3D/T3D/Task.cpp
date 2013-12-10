// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// task.cpp
//
// Abstract base class for tasks
// Ideas from http://www.gamedev.net/page/resources/_/technical/game-programming/enginuity-part-iv-r1973

#include "Task.h"

namespace T3D
{

	Task::Task(T3DApplication* app) :app(app)
	{
		finished = false;
	}


	Task::~Task(void)
	{
	}

}
