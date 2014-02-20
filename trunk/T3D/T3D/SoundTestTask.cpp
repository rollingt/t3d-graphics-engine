#include "SoundTestTask.h"
#include "Input.h"

namespace T3D{

	SoundTestTask::SoundTestTask(T3DApplication *app) : Task(app)
	{
		music = app->soundManager->createMusic("Resources/oddity.mp3");
		sound = app->soundManager->createSound("Resources/beep.wav");
	}


	SoundTestTask::~SoundTestTask(void)
	{
	}

	void SoundTestTask::update(float dt){
		if (Input::keyDown[KEY_SPACE]){
			sound->play();
		}
		if (Input::keyDown[KEY_P]){
			if (music->isPlaying()){
				music->pause();
			} else {
				music->play();
			}
		}
	}

}
