#include "Sound.h"

namespace T3D{

	Sound::Sound(std::string filename)
	{
		theSound = Mix_LoadWAV(filename.c_str());
	}


	Sound::~Sound(void)
	{
		if (theSound)
			Mix_FreeChunk(theSound);
	}

	void Sound::play(){
		Mix_PlayChannel(-1,theSound,0);
	}

}
