// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Sound.h
//
// Simple class used for playing short sound files.  Uses FMod: www.fmod.org

#pragma once

#include "fmod/fmod.hpp"
#include "SoundManager.h"

namespace T3D {

	//! \brief Play and adjust sounds loaded by a SoundManager.
	class Sound
	{
	friend class SoundManager;
	public:
		Sound(SoundManager* sm) : soundManager(sm),
								  theSound    (nullptr),
								  channel     (nullptr),
								  volume      (0.01f) { }

		~Sound(void) = default;

		void play();	
		void setVolume(float v);

	private:
		SoundManager* soundManager;
		FMOD::Sound *theSound;
		FMOD::Channel *channel;

		float volume;
	};

}

