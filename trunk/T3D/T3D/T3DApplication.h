// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// t3dapplication.cpp
//
// Abstract base class for a T3D application
// Stores reference to root transform of scene graph and list of tasks

#ifndef T3DAPPLICATION_H
#define T3DAPPLICATION_H

#include "Transform.h"
#include "renderer.h"
#include <vector>

using namespace std;

namespace T3D
{
	class Task;

	class T3DApplication
	{
	public:
		T3DApplication(void);
		virtual ~T3DApplication(void);

		virtual bool init() = 0;
		virtual int run() = 0;
		virtual void quit() = 0;
		virtual void updateTasks();
		virtual void updateComponents(Transform *t);

		Transform* getRoot(){return root;};
		Renderer* getRenderer(){return renderer;};

		void addTask(Task *t);
		void removeTask(Task *t);

	protected:
		bool running;
		Transform *root;
		Renderer *renderer;
		float lastFrame, dt;

	private:
		vector<Task*> tasks;
	};

}

#endif

