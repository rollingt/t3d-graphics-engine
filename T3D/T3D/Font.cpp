// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// Font.h
//
// TTF_Font wrapper for font cache

#include <iostream>
#include "Font.h"

namespace T3D{

	font::font(const char *filename, int pointSize)
	{
		name = filename;
		size = pointSize;

		ttf = TTF_OpenFont(filename, pointSize);
		if (ttf == NULL) {
			std::cout << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
		}

	}

	font::~font(void)
	{
		TTF_CloseFont(ttf);
	}

	// Returns true if the font at the absolute path 'filename' exists and is available
	// in at least 'pointSize' size
	bool font::matches_family_and_size(const char *filename, int pointSize)
	{
		return name.compare(filename) == 0 && size == pointSize;
	}
}
