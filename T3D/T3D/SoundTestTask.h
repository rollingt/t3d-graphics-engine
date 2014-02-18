#pragma once
#include "task.h"
#include "Sound.h"
#include "Music.h"

namespace T3D{

	class SoundTestTask :
		public Task
	{
	public:
		SoundTestTask(T3DApplication *app);
		~SoundTestTask(void);
		
		virtual void update(float dt);
	private:
		Sound *sound;
		Music *music;
	};

}

