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
		vector<Task*>::iterator it;

		for ( it=tasks.begin() ; it < tasks.end(); it++ )
		{
			delete (*it);
		}
	}
	

	void T3DApplication::addTask(Task *t){
		tasks.push_back(t);
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
		vector<Task*>::iterator it;

		for ( it=tasks.begin() ; it < tasks.end(); it++ )
		{
			(*it)->update(dt);
		}
	}

}
