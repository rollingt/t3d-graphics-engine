// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// FontCache.h
//
// SDL ttf font manager to allow reuse of loaded fonts
#pragma once

#include <vector>
#include "Font.h"

namespace T3D {

	//! \brief Manages a reusable collection of font families in different sizes.
	class FontCache
	{
	private:
		std::vector<font *> fonts;

	public:
		FontCache(void)  = default;
		~FontCache(void) = default;

		//! \brief Grab a font, hitting the cache first if its in memory.
		font *getFont(const char *filename, int pointSize);
	};

}
