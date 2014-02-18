#pragma once

#include <string>

#include <sdl\SDL_mixer.h>

namespace T3D{

	class Music
	{
	public:
		Music(std::string filename);
		~Music(void);

		void play();
		void pause();
		void stop();

	private:
		Mix_Music *theMusic;
	};

}

