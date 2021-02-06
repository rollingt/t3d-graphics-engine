// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// T3Dapplication.cpp
//
// Abstract base class for a T3D application
// Stores reference to root transform of scene graph and list of tasks
#pragma once

#include <list>

namespace T3D
{
	class Task;
	class Renderer;
	class Transform;
	class font;
	class SoundManager;

	//! \brief Base class for T3D driver applications, such as WinGLApplication.
	class T3DApplication
	{
	public:
		T3DApplication(void);
		virtual ~T3DApplication(void);

		virtual bool init() = 0;
		virtual int  run() = 0;
		virtual void quit() = 0;
		virtual void updateTasks();
		virtual void updateComponents(Transform *t);
		virtual font *getFont(const char *filename, int pointSize) { return NULL; }

		Transform* getRoot(){return root;};
		Renderer* getRenderer(){return renderer;};

		void addTask(Task *t);
		void removeTask(Task *t);
		Task *findTask(const char *name);
		bool validTask(Task *t);				// test that task is still alive

		SoundManager *soundManager;

	protected:
		bool running;
		Transform *root;
		Renderer *renderer;
		float lastFrame, dt;

	private:
		std::list<Task*> tasks;
	};

}
