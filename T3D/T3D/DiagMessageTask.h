// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// DiagMessageTask.h
//
// Onscreen diagnostic/debug messages

#pragma once

#include "Task.h"

namespace T3D 
{

	class Texture;

	//! \brief Class providing timed on-screen diagnostic messages.
	class DiagMessageTask :
		public Task
	{
	public:
		//! \brief Create DiagMessageTask that is hidden and not timed by default.
		DiagMessageTask(T3DApplication *app);

		//! \brief Create a DiagMessageTask with parameters.
		DiagMessageTask(T3DApplication *app, 
						const char *message, 
						int x, 
						int y, 
						bool timed = false, 
						float duration = 0.0f);

		//! \brief Destroy DiagMessageTask
		virtual ~DiagMessageTask(void);

		//! \brief Tick the DiagMessageTask.
		virtual void update(float dt);

		//! \brief Update the duration and timed status of the message.
		void setTimed(float duration);

		//! \brief Update the message and coordinates of the message
		void setMessage(const char *message, int x, int y);

	private:
		//! \brief Remove 2D overlay, unload the renderer resources and free memory.
		void removeOverlay();

	protected:
		std::string message;
		int x = 0;
		int y = 0;
		bool refresh = false;
		bool timed = false;
		float time = 0;
		Texture *diagOverlay = nullptr;
	};
}
