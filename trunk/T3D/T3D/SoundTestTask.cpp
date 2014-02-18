#include "SoundTestTask.h"
#include "Input.h"

namespace T3D{

	SoundTestTask::SoundTestTask(T3DApplication *app) : Task(app)
	{
		sound = new Sound("resources/beep.wav");
	}


	SoundTestTask::~SoundTestTask(void)
	{
	}

	void SoundTestTask::update(float dt){
		if (Input::keyDown[KEY_P]){
			sound->play();
		}
	}

}
