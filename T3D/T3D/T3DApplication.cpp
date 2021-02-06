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

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "T3DApplication.h"

#include "Transform.h"
#include "Renderer.h"
#include "Font.h"
#include "SoundManager.h"
#include "GameObject.h"
#include "Input.h"
#include "Task.h"

namespace T3D 
{
	T3DApplication::T3DApplication(void)
	{
		/* initialize random seed: */
		srand((unsigned int)time(NULL));

		lastFrame = 0.0f;
		dt = 0.0f;
		root = NULL;
		renderer = NULL;
		running = true;
		Input::init();
		soundManager = new SoundManager();
	}


	T3DApplication::~T3DApplication(void)
	{
		for (auto &task: tasks)
		{
			delete task;
		}
	}
	

	void T3DApplication::addTask(Task *t){
		tasks.push_back(t);
	}

	void T3DApplication::removeTask(Task *t){
		tasks.remove(t);
	}

	Task *T3DApplication::findTask(const char *name)
	{
		for (auto task : tasks)
		{
			if (task->getName().compare(name) == 0) return task;
		}
		return nullptr;	// task not found
	}

	bool T3DApplication::validTask(Task *t)				// test that task is still alive
	{
		return (std::find(tasks.begin(), tasks.end(), t) != tasks.end());
	}

	void T3DApplication::updateComponents(Transform *t) {
		if (t->gameObject) t->gameObject->update(dt); /* Update root     */

		for (auto &child : t->children)               /* Update children */
		{
			updateComponents(child);
		}
	}

	void T3DApplication::updateTasks() {
		auto it = tasks.begin();

		while (it != tasks.end()) {
			auto task = *it;
			task->update(dt);

			if (task->getFinished()) {
				auto finishedTask = *it;
				it = tasks.erase(it);
				delete finishedTask;
			}
			else {
				it++;
			}
		}
	}

}
