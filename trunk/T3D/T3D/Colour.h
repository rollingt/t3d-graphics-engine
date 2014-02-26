// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Colour.h
//
// Simple colour class

#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

namespace T3D
{
	class Colour
	{
	public:
		Colour(int r, int g, int b, int a) : r(r), b(b), g(g), a(a){}

		Colour(uint32_t hex){
			r = (hex >> 24) & 0xff;
			g = (hex >> 16) & 0xff;
			b = (hex >> 8) & 0xff;
			a = hex & 0xff;
		}

		~Colour(void);

		int r,g,b,a;
	};
}

#endif

