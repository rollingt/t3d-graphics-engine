// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// DrawTask.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#pragma once
#include "task.h"
#include "T3DApplication.h"
#include "Texture.h"

namespace T3D{

	class DrawTask :
		public Task
	{
	public:
		DrawTask(T3DApplication *app, Texture* tex);
		~DrawTask(void);

		void init();
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);

		virtual void update(float dt);

	private:
		Texture *drawArea;

		void pushPixel(int x, int y, Colour colour);
		void flushPixelQueue();

		struct Pixel
		{
			int x = 0;
			int y = 0;
			Colour colour = { 0xFF, 0, 0xFF, 0xFF }; // Anything dodgy should show up as purple.
		};
		std::vector<Pixel> pixelPlotQueue;
	};

}

