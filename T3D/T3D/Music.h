// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Music.h
//
// Simple class used for streaming large sound files.  Uses FMod: www.fmod.org

#pragma once

#include <string>
#include "fmod/fmod.hpp"
#include "SoundManager.h"

namespace T3D{

	//! \brief Play, pause and adjust sounds loaded by a SoundManager.
	class Music
	{
	friend class SoundManager;
	public:
		Music::Music(SoundManager* sm) : soundManager(sm),
										 channel     (nullptr),
										 theMusic    (nullptr),
										 volume      (1.0f) { }
		~Music(void) = default;

		void play();	
		void pause();
		void stop();
		void setVolume(float v);	
		bool isPlaying();

	private:
		SoundManager* soundManager;
		FMOD::Sound *theMusic;
		FMOD::Channel *channel;

		float volume;
	};
}

