#include <iostream>
#include <string>
#include "Music.h"

namespace T3D{

	Music::Music(std::string filename)
	{
		theMusic = Mix_LoadMUS(filename.c_str());
		if (!theMusic)
			std::cout<<"Problem loading music: " << Mix_GetError() << "\n";
	}


	Music::~Music(void)
	{
		if (theMusic)
			Mix_FreeMusic(theMusic);
	}
	
	void Music::play(){ 
        if( Mix_PlayingMusic() == 0 )
        {
            Mix_PlayMusic(theMusic, -1 );
        }
        else
        {
            if( Mix_PausedMusic() == 1 )
            {
                Mix_ResumeMusic();
            }
        }
	}

	void Music::pause(){
		if( Mix_PlayingMusic() == 1 )
        {
            Mix_PauseMusic();
        }
	}

	void Music::stop(){
		Mix_HaltMusic();
	}


}
