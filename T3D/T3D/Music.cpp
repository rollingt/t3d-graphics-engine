// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Music.cpp
//
// Simple class used for streaming large sound files.  Uses FMod: www.fmod.org

#include "Music.h"
#include "Logger.h"

namespace T3D{

	void Music::play(){
		if (channel){			
            channel->setPaused(false);
		} else {
			soundManager->system->playSound(FMOD_CHANNEL_FREE, theMusic, true, &channel);
			channel->setVolume(volume);
			channel->setPaused(false);
		}

		logger::Log(priority::Tracing,
					output_stream::File,
					category::Audio,
					"Started playing music...");
	}

	void Music::setVolume(float v){		
		volume = v;

		if (channel){
			channel->setVolume(volume);
		}
	}

	void Music::pause(){
		if (channel) {
            channel->setPaused(true);
		}

		logger::Log(priority::Tracing,
					output_stream::File,
					category::Audio,
					"Paused music...");
	}
	
	void Music::stop(){		
		if (channel) {
			channel->stop();
			channel = NULL;
		}

		logger::Log(priority::Tracing,
					output_stream::File,
					category::Audio,
					"Stopped music...");
	}

	bool Music::isPlaying(){
		if (channel){
			bool paused;
			channel->getPaused(&paused);
			return !paused;
		} else {
			return false;
		}
	}

}
