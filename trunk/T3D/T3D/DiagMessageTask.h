// =========================================================================================
// 
// =========================================================================================
//
// Author: David Pentecost
//
// DiagMessageTask.h
//
// Onscreen diagnostic/debug messages

#ifndef DIAGMESSAGETASK_H
#define DIAGMESSAGETASK_H

#include "task.h"

namespace T3D{
	class DiagMessageTask :
		public Task
	{
	public:
		DiagMessageTask(T3DApplication *app);
		DiagMessageTask(T3DApplication *app, const char *message, int x, int y, bool timed=false, float duration=0.0f);
		virtual ~DiagMessageTask(void);

		virtual void update(float dt);

		void setTimed(float duration);

		void setMessage(const char *message, int x, int y);
	private:
		void removeOverlay();

	protected:
		std::string message;
		int x,y;
		bool refresh;
		bool timed;
		float time;
		Texture *diagOverlay;
	};
}

#endif
