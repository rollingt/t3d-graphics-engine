#include "Sound.h"

namespace T3D{

	Sound::Sound(SoundManager* sm) : soundManager(sm)
	{
		channel = NULL;
		volume = 0.01; 
	}


	Sound::~Sound(void)
	{
	}

	void Sound::play(){
		soundManager->system->playSound(FMOD_CHANNEL_FREE, theSound, true, &channel);
		channel->setVolume(volume); 
		channel->setPaused(false);
	}

	void Sound::setVolume(float v){
		volume = v;
	}
}
