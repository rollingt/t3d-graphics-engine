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
		int x_1, y_1, x_2, y_2;//vertices for polygon 
		int x_axis = 1024; int y_axis = 640;
		Vector3 vector3[3];
		Matrix3x3 matrix3;

		~DrawTask(void);


		void init();
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);
		void drawCircleTrigonometry(int centrex, int centrey, int radius, Colour c);
		void drawCircleOPFour(int centrex, int centrey, int radius, Colour c);
		void drawCircleOPEight(int centrex, int centrey, int radius, Colour c);
		void drawCirclePythagoras(int centrex, int centrey, int radius, Colour c);
		void drawPolygon(Vector3 vector[], Colour c);//x1 and y1 will be centre of drawing plane 
		bool inRange(int x, int y);
		virtual void update(float dt);
		Matrix3x3 getTranslationMatrix(int offsetx, int offsety);
		void drawTranslatePolygon(Colour c);
		void drawScalePolygon(Colour c);
		void drawRotatePolygon(Colour c);

	private:
		Texture *drawArea;
	};

}

