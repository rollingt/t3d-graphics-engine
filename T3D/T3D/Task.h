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
#pragma once

#include <string>
#include "T3DApplication.h"

namespace T3D
{
	//! \brief Timed, searchable application-level tasks.
	/*
	 * T3D Tasks are the smallest unit of work T3DApplication instances can schedule.
	 * Tasks can do arbitrary things and have access to the rendering context. 
	 * For example, 2D drawing tasks and debug message tasks.
	 *
	 * A common way of implementing interlinked movies/animations is to subclass Task,
	 * creating a centralized way to tick many different GameObjects - this is covered in the tutorials.
	 */
	class Task
	{
	public:
		//! \brief Create Task
		Task(T3DApplication *app) : app(app), 
									finished(false) { }

		//! \brief Destroy Task (trivially)
		virtual ~Task(void) = default;

		//! \brief Tick Task.
		virtual void update(float dt) = 0;

		// Accessors
		bool getFinished()              { return finished; }
		void setFinished(bool finished) { this->finished = finished; }

		std::string& getName()         { return name; }
		void setName(const char *name) { this->name = name; }


	private:
		std::string name;					// task name
		bool finished;						// task has finished and can be removed and deleted from tasks

	protected:
		T3DApplication *app;
	};

}
