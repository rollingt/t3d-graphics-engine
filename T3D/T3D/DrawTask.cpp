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
		x_1 = 700; y_1 = 100;
		x_2 = 800; y_2 = 200;
		x_axis = 1024; y_axis = 640;
		init();		
	}


	DrawTask::~DrawTask(void)
	{
	}

	void DrawTask::init(){		
		drawArea->clear(Colour(255,255,255,255));
		update(1.0);
		//drawBresLine(0, 0, 500, 200, Colour(0, 0, 0, 255));
		//drawBresLine(110, 0, 110, 200, Colour(0, 0, 0, 255));
		//drawCircleTrigonometry(500, 300, 300, Colour(0, 0, 0, 255));
		//drawCircleOPFour(500, 300, 300, Colour(0, 0, 0, 255));
		//drawCircleOPEight(500, 300, 300, Colour(0, 0, 0, 255));
		//drawCirclePythagoras(500, 300, 300, Colour(0, 0, 0, 255));
		//drawPolygon(vector3, Colour(0, 0, 0, 255));
	}	

	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2,Colour c){
		int temp = 0;
		int stop_temp = 0;
		if (inRange(x1, y1) && inRange(x2, y2)) {
			//if x1 == x2 vertical line 
			if (x1 == x2) {
				if (y1 < y2) {
					temp = y1;
					stop_temp = y2;
				}
				else {
					temp = y2;
					stop_temp = y1;
				}

				for (int i = temp; i <= stop_temp; i++) {
					drawArea->plotPixel(x1, i, c);
				}
			}
			//if y1 = y2 horizontal
			else if (y1 == y2) {
				for (int i = x1; i <= x2; i++) {
					drawArea->plotPixel(i, y1, c);
				}
			}
			else {
				if (x1 < x2) {
					float ystep = float(y2 - y1) / (x2 - x1);
					float y = y1;
					for (int x = x1; x < x2; x++) {
						drawArea->plotPixel(x, int(y), c);
						y += ystep;
					}
				}
				else {
					float ystep = float(y1 - y2) / (x1 - x2);
					float y = y2;
					for (int x = x2; x < x1; x++) {
						drawArea->plotPixel(x, int(y), c);
						y += ystep;
					}
				}

			}
		}		
	}
		
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2,Colour c){
		
		//if x1 == x2 vertical line 
		if (x1 == x2) {
			int temp = 0;
			int stop_temp = 0;
			if (y1 < y2) {
				temp = y1;
				stop_temp = y2;
			}
			else {
				temp = y2;
				stop_temp = y1;
			}

			for (int i = temp; i <= stop_temp; i++) {
				drawArea->plotPixel(x1, i, c);
			}
		}
		//if y1 = y2 horizontal
		else if (y1 == y2) {
			for (int i = x1; i <= x2; i++) {
				drawArea->plotPixel(i, y1, c);
			}
		}
		else {
			if (x1 < x2) {
				int deltay = y2 - y1;
				int deltax = x2 - x1;
				int error = deltax / 2;
				int y = y1;
				for (int x = x1; x <= x2; x++) {
					drawArea->plotPixel(x, y, c);
					error = error - deltay;
					if (error < 0) {
						y += 1;
						error += deltax;
					}
				}
			}
			else {
				int deltay = y1 - y2;
				int deltax = x1 - x2;
				int error = deltax / 2;
				int y = y2;
				for (int x = x2; x <= x1; x++) {
					drawArea->plotPixel(x, y, c);
					error = error - deltay;
					if (error < 0) {
						y += 1;
						error += deltax;
					}
				}
			}			
		}
	}

	void DrawTask::drawCircleTrigonometry(int centrex, int centrey, int radius, Colour c)
	{
		float pi = 2.0 * acos(0.0);//initialize PI value
		float step = 0.0005;
		int x,y; //coordinates of point we are trying to plot  
		
		for (float theta = 0.0; theta < (2 * pi); theta += step) {
			x =(int) centrex + (radius * cos(theta));
			y = (int) centrey + (radius * sin(theta));
			printf("%d , %d \n", x, y);
			drawArea->plotPixel(x, y, c);
		}
	}

	void DrawTask::drawCircleOPFour(int centrex, int centrey, int radius, Colour c)
	{
		float pi = 2.0 * acos(0.0);//initialize PI value
		float step = 0.0005;
		int x, y; //coordinates of point we are trying to plot  

		for (float theta = 0.0; theta < (pi/2); theta += step) {
			x = (int)(radius * cos(theta));
			y = (int)(radius * sin(theta));
			printf("%d , %d \n", x, y);
			drawArea->plotPixel((centrex + x), (centrey + y), c);
			drawArea->plotPixel((centrex + x), (centrey - y), c);
			drawArea->plotPixel((centrex - x), (centrey + y), c);
			drawArea->plotPixel((centrex - x), (centrey - y), c);
		}
	}

	void DrawTask::drawCircleOPEight(int centrex, int centrey, int radius, Colour c)
	{
		float pi = 2.0 * acos(0.0);//initialize PI value
		float step = 0.0005;
		int x, y; //coordinates of point we are trying to plot  

		for (float theta = 0.0; theta < (pi / 4); theta += step) {
			x = (int)(radius * cos(theta));
			y = (int)(radius * sin(theta));
			printf("%d , %d \n", x, y);
			drawArea->plotPixel((centrex + x), (centrey + y), c); drawArea->plotPixel((centrex + y), (centrey + x), c);
			drawArea->plotPixel((centrex + x), (centrey - y), c); drawArea->plotPixel((centrex - y), (centrey + x), c);
			drawArea->plotPixel((centrex - x), (centrey + y), c); drawArea->plotPixel((centrex + y), (centrey - x), c);
			drawArea->plotPixel((centrex - x), (centrey - y), c); drawArea->plotPixel((centrex - y), (centrey - x), c);
		}
	}

	void DrawTask::drawCirclePythagoras(int centrex, int centrey, int radius, Colour c)
	{
		float step = 0.0005;
		int x, y; //coordinates of point we are trying to plot
		for (y = 0; y <= (radius / sqrt(2)); y++) {
			x = sqrt((radius * radius) - (y * y));
			drawArea->plotPixel((centrex + x), (centrey + y), c); drawArea->plotPixel((centrex + y), (centrey + x), c);
			drawArea->plotPixel((centrex + x), (centrey - y), c); drawArea->plotPixel((centrex - y), (centrey + x), c);
			drawArea->plotPixel((centrex - x), (centrey + y), c); drawArea->plotPixel((centrex + y), (centrey - x), c);
			drawArea->plotPixel((centrex - x), (centrey - y), c); drawArea->plotPixel((centrex - y), (centrey - x), c);
		}
	}

	void DrawTask::drawPolygon(Vector3 vector[], Colour c)
	{
		int x1, y1, x2, y2;
		for (int i = 0; i <= 1; i++) {			
			x1 = vector[i].x;
			y1 = vector[i].y;
			x2 = vector[i+1].x;
			y2 = vector[i+1].y;
			drawDDALine(x1, y1, x2, y2, c);
			if (i == 1) {
				x1 = vector[i+1].x;
				y1 = vector[i+1].y;
				x2 = vector[i - 1].x;
				y2 = vector[i - 1].y;
				drawDDALine(x1, y1, x2, y2, c);
			}
		}						
	}

	bool DrawTask::inRange(int x, int y)
	{		
		if((x <= x_axis)&&(y <=y_axis )){			
			return true;

		}
		else {					
			return false;			
		}		
	}
	
	void DrawTask::update(float dt){
		//drawArea->clear(Colour(255,255,255,255));
		//drawPolygon(x_1, y_1, x_2, y_2, Colour(0, 0, 0, 255));
		
		
		vector3[0].x = (x_axis / 2)-100;
		vector3[0].y = (y_axis / 2)-100;
		vector3[0].z = 1;

		vector3[1].x = x_1-100;
		vector3[1].y = y_1-100;
		vector3[1].z = 1-100;

		vector3[2].x = x_2-100;
		vector3[2].y = y_2-100;
		vector3[2].z = 1-100;
		drawPolygon(vector3, Colour(0, 0, 0, 255));
		//drawTranslatePolygon(Colour(0, 0, 0, 255));
		//drawScalePolygon(Colour(0, 0, 0, 255));
		drawRotatePolygon(Colour(0, 0, 0, 255));
		app->getRenderer()->reloadTexture(drawArea);
	}

	Matrix3x3 DrawTask::getTranslationMatrix(int offsetx, int offsety)
	{
		Matrix3x3 translate_matrix(1,0,offsetx,
			0,1,offsety,
			0,0,1);		
		
		return translate_matrix;
	}

	void DrawTask::drawTranslatePolygon(Colour c)
	{
		int x1, y1, x2, y2;
		Matrix3x3 translation_matrix=getTranslationMatrix(100,100);
		Vector3 translated_vector[3];
		for (int i = 0; i <= 1; i++) {
			translated_vector[i] = translation_matrix.operator*(vector3[i]);
			translated_vector[i + 1] = translation_matrix.operator*(vector3[i+1]);
			x1 = translated_vector[i].x;
			y1 = translated_vector[i].y;
			x2 = translated_vector[i + 1].x;
			y2 = translated_vector[i + 1].y;
			drawDDALine(x1, y1, x2, y2, c);
			if (i == 1) {
				x1 = translated_vector[i + 1].x;
				y1 = translated_vector[i + 1].y;
				x2 = translated_vector[i - 1].x;
				y2 = translated_vector[i - 1].y;
				drawDDALine(x1, y1, x2, y2, c);
			}
		}
	}
	void DrawTask::drawScalePolygon(Colour c)
	{
		Matrix3x3 scale_matrix(1.1, 0, 0,
			0, 1.1, 0,
			0, 0, 1);
		int x1, y1, x2, y2;		
		Vector3 scaled_vector[3];
		for (int i = 0; i <= 1; i++) {
			scaled_vector[i] = scale_matrix.operator*(vector3[i]);
			scaled_vector[i + 1] = scale_matrix.operator*(vector3[i + 1]);
			x1 = scaled_vector[i].x;
			y1 = scaled_vector[i].y;
			x2 = scaled_vector[i + 1].x;
			y2 = scaled_vector[i + 1].y;
			drawDDALine(x1, y1, x2, y2, c);
			if (i == 1) {
				x1 = scaled_vector[i + 1].x;
				y1 = scaled_vector[i + 1].y;
				x2 = scaled_vector[i - 1].x;
				y2 = scaled_vector[i - 1].y;
				drawDDALine(x1, y1, x2, y2, c);
			}
		}
	}
	void DrawTask::drawRotatePolygon(Colour c)
	{
		int angle=90;//rotation angle
		Matrix3x3 rotate_matrix(cos(angle), -sin(angle), 0,
			sin(angle), cos(angle), 0,
			0, 0, 1);
		int x1, y1, x2, y2;
		Vector3 rotate_vector[3];
		for (int i = 0; i <= 1; i++) {
			rotate_vector[i] = rotate_matrix.operator*(vector3[i]);
			rotate_vector[i + 1] = rotate_matrix.operator*(vector3[i + 1]);
			x1 = rotate_vector[i].x;
			y1 = rotate_vector[i].y;
			x2 = rotate_vector[i + 1].x;
			y2 = rotate_vector[i + 1].y;
			drawDDALine(x1, y1, x2, y2, c);
			if (i == 1) {
				x1 = rotate_vector[i + 1].x;
				y1 = rotate_vector[i + 1].y;
				x2 = rotate_vector[i - 1].x;
				y2 = rotate_vector[i - 1].y;
				drawDDALine(x1, y1, x2, y2, c);
			}
		}
	}
}
