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

#include "T3DApplication.h"
#include "Input.h"
#include "Task.h"

namespace T3D 
{

	T3DApplication::T3DApplication(void)
	{
		root = NULL;
		Input::init();
	}


	T3DApplication::~T3DApplication(void)
	{
		list<Task*>::iterator it;

		for ( it=tasks.begin() ; it != tasks.end(); it++ )
		{
			delete (*it);
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
		list<Task*>::iterator it;

		for ( it=tasks.begin() ; it != tasks.end(); it++ )
		{
			if ((*it)->getName().compare(name) == 0)
				return (*it);
		}
		return NULL;			// task not found
	}

	bool T3DApplication::validTask(Task *t)				// test that task is still alive
	{
		std::list<Task*>::iterator it = std::find(tasks.begin(), tasks.end(), t);
		return it != tasks.end();
	}

	void T3DApplication::updateComponents(Transform *t){
		if (t->gameObject!=NULL)
		{
			t->gameObject->update(dt);
		}

		for(int i = 0; i < t->children.size(); ++i)
		{
			updateComponents(t->children[i]);
		}
	}

	void T3DApplication::updateTasks(){
		list<Task*>::iterator it=tasks.begin();
		bool taskFinished;
		Task *task;

		while (it != tasks.end())
		{
			task = (*it);

			taskFinished = task->getFinished();

			if (!taskFinished)
				task->update(dt);			// only update still active tasks (not finished)

			it++;							// next (must be before deleting any finished task)

			if (taskFinished)
			{
				// remove and delete finished task
				tasks.remove(task);
				delete task;
			}
		}
	}

}
