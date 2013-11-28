// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// perflogtask.h
//
// Simple class to track framerates and write to file when app closes

#ifndef PERFLOGTASK_H
#define PERFLOGTASK_H

#include "task.h"

namespace T3D{
	class PerfLogTask :
		public Task
	{
	public:
		PerfLogTask(void);
		virtual ~PerfLogTask(void);

		virtual void update(float dt);

	protected:
		long int frameCount;
		float elapsedTime;
		float dtmin;
		float dtmax;

		virtual void log();
	};
}

#endif

