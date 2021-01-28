// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// SoundManager.cpp
//
// Simple class used for managing Sound and Music objects.  Uses FMod: www.fmod.org

#include <iostream>

#include "SoundManager.h"
#include "Sound.h"
#include "Music.h"

namespace T3D{

	SoundManager::SoundManager(void)
	{
		system = NULL;
	}


	SoundManager::~SoundManager(void)
	{
	}

	void SoundManager::errorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		}
	}
	
	void SoundManager::update(){
		system->update();
	}
	
	void SoundManager::init(){
		FMOD_RESULT result;
		unsigned int version;
		int numdrivers;
#pragma warning(suppress: 26812) /* unscoped enum warning */
		FMOD_SPEAKERMODE speakermode;
		FMOD_CAPS caps;
		char name[256];
		/*
		Create a System object and initialize.
		*/
		result = FMOD::System_Create(&system);
		errorCheck(result);
		result = system->getVersion(&version);
		errorCheck(result);

		if (version < FMOD_VERSION)
		{
			printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n",
			version, FMOD_VERSION);
		}

		result = system->getNumDrivers(&numdrivers);
		errorCheck(result);

		if (numdrivers == 0)
		{
			result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
			errorCheck(result);
		}
		else
		{
			result = system->getDriverCaps(0, &caps, 0, &speakermode);
			errorCheck(result);
			/*
			Set the user selected speaker mode.
			*/
			result = system->setSpeakerMode(speakermode);
			errorCheck(result);	
			if (caps & FMOD_CAPS_HARDWARE_EMULATED)
			{
				std::cout << "acceleration off\n";
				/*
				The user has the 'Acceleration' slider set to off! This is really bad
				for latency! You might want to warn the user about this.
				*/
				result = system->setDSPBufferSize(1024, 10);
				errorCheck(result);			
			}
			result = system->getDriverInfo(0, name, 256, 0);
			errorCheck(result);
			if (strstr(name, "SigmaTel"))
			{
				std::cout << "sigmatel\n";
				/*
				Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
				PCM floating point output seems to solve it.
				*/
				result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,
				FMOD_DSP_RESAMPLER_LINEAR);
				errorCheck(result);
			}
		}
		result = system->init(100, FMOD_INIT_NORMAL, 0);
		if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
		{
			std::cout << "speaker\n";
			/*
			Ok, the speaker mode selected isn't supported by this soundcard. Switch it
			back to stereo...
			*/
			result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
			errorCheck(result);
			/*
			... and re-init.
			*/
			result = system->init(100, FMOD_INIT_NORMAL, 0);			
		}
		errorCheck(result);
	}

	Music* SoundManager::createMusic(std::string filename){
		FMOD_RESULT result;

		Music* newMusic = new Music(this);
		result = system->createStream(filename.c_str(), FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &newMusic->theMusic);
		errorCheck(result);
		return newMusic;
	}
	
	Sound* SoundManager::createSound(std::string filename){
		Sound* newSound = new Sound(this);
		system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &newSound->theSound);
		return newSound;
	}
	

}
