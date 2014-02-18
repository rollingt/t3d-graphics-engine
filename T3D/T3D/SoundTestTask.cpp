#include "SoundTestTask.h"
#include "Input.h"

namespace T3D{

	SoundTestTask::SoundTestTask(T3DApplication *app) : Task(app)
	{
		sound = new Sound("resources/beep.wav");
		music = new Music("resources/example.ogg");
	}


	SoundTestTask::~SoundTestTask(void)
	{
	}

	void SoundTestTask::update(float dt){
		if (Input::keyDown[KEY_SPACE]){
			sound->play();
		}
		if (Input::keyDown[KEY_P]){
			music->play();
		}
	}

}
