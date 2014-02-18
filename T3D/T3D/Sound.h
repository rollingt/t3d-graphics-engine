#pragma once

#include <string>

#include <sdl\SDL_mixer.h>

namespace T3D{

	class Sound
	{
	public:
		Sound(std::string filename);
		~Sound(void);

		void play();

	private:
		Mix_Chunk *theSound;
	};

}

