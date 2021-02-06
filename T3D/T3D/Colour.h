// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Colour.h
//
// Simple colour class
#pragma once

#include <stdint.h>

namespace T3D
{
	//! \brief A simple Colour class, where colour channels and alpha are integers ranging 0-255.
	class Colour
	{
	public:
		//! \brief Create Colour (trivially)
		Colour(int r, int g, int b, int a) : r(r), b(b), g(g), a(a) { }

		//! \brief Create Colour from a 32-bit dword. 
		Colour(uint32_t hex){
			r = (hex >> 24) & 0xff;
			g = (hex >> 16) & 0xff;
			b = (hex >> 8) & 0xff;
			a = hex & 0xff;
		}

		//! \brief Destroy Colour (trivially)
		~Colour(void) = default;

		int r,g,b,a;
	};
}
