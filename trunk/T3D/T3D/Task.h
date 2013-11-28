// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// task.h
//
// Abstract base class for tasks
// Ideas from http://www.gamedev.net/page/resources/_/technical/game-programming/enginuity-part-iv-r1973

#ifndef TASK_H
#define TASK_H

namespace T3D
{

	class Task
	{
	public:
		Task(void);
		virtual ~Task(void);

		virtual void update(float dt) = 0;
	};

}

#endif

