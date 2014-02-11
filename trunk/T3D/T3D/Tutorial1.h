#pragma once
#include "winglapplication.h"
#include "Texture.h"
#include "DrawTask.h"

namespace T3D{

	class Tutorial1 :
		public WinGLApplication
	{
	public:
		Tutorial1(void);
		~Tutorial1(void);

		bool init();


	private:
		Texture *drawArea;
		DrawTask *drawTask;

	};

}

