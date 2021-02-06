// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// SoundManager.h
//
// Simple class used for managing Sound and Music objects.  Uses FMod: www.fmod.org

#pragma once

#include <string>

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

namespace T3D {
	
	class Sound;
	class Music;

	//! \brief Create, load and update sounds and music.
	class SoundManager
	{
	friend class Sound;
	friend class Music;
	public:
		SoundManager(void) : system(nullptr) { }
		virtual ~SoundManager(void) = default;

		void init();
		void update();

		Sound* createSound(std::string filename);
		Music* createMusic(std::string filename);

	private:		
		FMOD::System *system;
		void errorCheck(FMOD_RESULT result);
	};

}

