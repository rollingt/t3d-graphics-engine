// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#include <math.h>
#include "DrawTask.h"

namespace T3D {

	// Creates a DrawTask that draws onto the Texture tex once per frame.
	//
	// Usage notes:
	// - `tex` should be initialised, and registered with the renderer as both a loaded Texture and a 2D Overlay.
	//   This can be done using `new Texture(...)`, `loadTexture(...)`, and finally `add2DOverlay(...)`.
	//
	// - If nothing is drawing on the screen, ensure the returned DrawTask object is added to the list of Tasks from the callsite using `addTask(...).
	//
	// - If there is nothing on the screen still, check the visual studio console for error messages in case something is out of bounds.
	DrawTask::DrawTask(T3DApplication *app, Texture* tex) : Task(app)
	{
		drawArea = tex;

		// Reserve some space for the buffer, as it's extremely unlikely just one pixel will be plotted, and
		// the common case is filled, non-sparse shapes
		const uint32_t pixelsToReserve = 512;
		pixelPlotQueue.reserve(pixelsToReserve);

		init();
	}

	// Add a pixel to be displayed this frame to the PixelPlotQueue.
	void DrawTask::pushPixel(int x, int y, Colour colour)
	{
		pixelPlotQueue.push_back(Pixel { x, y, colour }); 
	}

	// Plots every pixel pushed to the DrawTask's pixel queue this frame before clearing the queue.
	// If a pixel's X or Y coordinate is outside the drawable surface bounds, an error message is reported to stdout.
	// Otherwise, the pixel is written to the surface.
	void DrawTask::flushPixelQueue()
	{
		for (auto &Pixel : pixelPlotQueue)
		{
			bool PixelWithinWidth  = (Pixel.x >= 0 && Pixel.x < drawArea->getWidth());
			bool PixelWithinHeight = (Pixel.y >= 0 && Pixel.y < drawArea->getHeight());
			bool PixelWithinBounds = (PixelWithinWidth && PixelWithinHeight);

			if (PixelWithinBounds)
			{
				drawArea->plotPixel(Pixel.x, Pixel.y, Pixel.colour);
			}
			else
			{
				printf("Pixel out of bounds!\n"
					   "\tWidth  :: [0 <= X <= %4u :: %4d :: %5s]\n"
					   "%s"
					   "\tHeight :: [0 <= Y <= %4u :: %4d :: %5s]\n"
					   "%s"
					   ,
					   T3D::WindowWidth,
					   Pixel.x, PixelWithinWidth  ? "OK" : "ERROR",
					   PixelWithinWidth  ?   ""  : "                                      ^^^\n",
					   T3D::WindowHeight,
					   Pixel.y, PixelWithinHeight ? "OK" : "ERROR",
					   PixelWithinHeight  ?  ""  : "                                      ^^^\n");
			}
		}

		pixelPlotQueue.clear();
	}


	// Ensures all pre-conditions are met for following calls to the `update` function.
	// NOTE(Evan): This should really be inlined into the constructor or at least made private.
	void DrawTask::init	(){		
		drawArea->clear(Colour(255,255,255,255));
		drawDDALine(100,100,200,200,Colour(0,0,0,255));
	}


	// Draw a coloured line from (x1, y1) to (x2, y2) using the floating-point 
	// Digital Differential Algorithm (DDA) algorithm from the 2D drawing lectures.
	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2,Colour c){
		float ystep = float(y2-y1)/(x2-x1);
		float y = float(y1);
		for (int x = x1; x<x2; x++){
			pushPixel(x, int(y), c);
			y += ystep;
		}
	}
		

	// Draw a coloured line from (x1, y1) to (x2, y2) using the integer-only
	// Bresenham algorithm from the 2D drawing lectures.
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2,Colour c)
	{ /* UNIMPLEMENTED */ }


	// Provides one frames' worth of pixels to draw onto the screen.
	void DrawTask::update(float dt){
		drawArea->clear(Colour(255, 255, 255, 255));
		drawDDALine(100, 10000, 200, 200, Colour(255,0,0,255));

		// Plots pixels made to the drawing area this frame and clears the pixel queue.
		flushPixelQueue();
		app->getRenderer()->reloadTexture(drawArea);
	}


}
