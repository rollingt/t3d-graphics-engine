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

#include "T3DApplication.h"

namespace T3D
{

	class Task
	{
	public:
		Task(T3DApplication *app);
		virtual ~Task(void);

		virtual void update(float dt) = 0;

		bool getFinished() { return finished; }
		void setFinished(bool finished) { this->finished = finished; }
		std::string& getName() { return name; }
		void setName(const char *name) { this->name = name; }

	private:
		std::string name;					// task name
		bool finished;						// task has finished and can be removed and deleted from tasks

	protected:
		T3DApplication *app;
	};

}

#endif

