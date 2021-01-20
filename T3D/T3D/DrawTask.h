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
		// Creates a DrawTask that draws onto the Texture tex once per frame.
		//
		// Usage notes:
		// - `tex` should be initialised, and registered with the renderer as both a loaded Texture and a 2D Overlay.
		//   This can be done using `new Texture(...)`, `loadTexture(...)`, and finally `add2DOverlay(...)`.
		//
		// - If nothing is drawing on the screen, ensure the returned DrawTask object is added to the list of Tasks from the callsite using `addTask(...).
		//
		// - If there is nothing on the screen still, check the visual studio console for error messages in case something is out of bounds.
		DrawTask(T3DApplication *app, Texture* tex);
		~DrawTask(void) = default;


		// Ensures all pre-conditions are met for following calls to the `update` function.
		// NOTE(Evan): This should really be inlined into the constructor or at least made private.
		void init();

		// Draw a coloured line from (x1, y1) to (x2, y2) using the floating-point 
		// Digital Differential Algorithm (DDA) algorithm from the 2D drawing lectures.
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);

		// Draw a coloured line from (x1, y1) to (x2, y2) using the integer-only
		// Bresenham algorithm from the 2D drawing lectures.
		// FIXME:
		// - Not implemented yet! That's your job.
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);

		// Provides one frames' worth of pixels to draw onto the screen.
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

