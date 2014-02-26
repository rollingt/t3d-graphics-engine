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

	DrawTask::DrawTask(T3DApplication *app, Texture* tex) : Task(app)
	{
		drawArea = tex;
		init();
	}


	DrawTask::~DrawTask(void)
	{
	}

	void DrawTask::init(){		
		drawArea->clear(Colour(255,255,255,255));
		drawDDALine(100,100,200,200,Colour(0,0,0,255));
	}

	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2,Colour c){
		float ystep = float(y2-y1)/(x2-x1);
		float y = y1;
		for (int x = x1; x<x2; x++){
			drawArea->plotPixel(x,int(y),c);
			y += ystep;
		}
	}
		
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2,Colour c){
	}

	void DrawTask::update(float dt){
		//drawArea->clear(Colour(255,255,255,255));

		app->getRenderer()->reloadTexture(drawArea);
	}

}
