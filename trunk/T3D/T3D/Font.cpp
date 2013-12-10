// =========================================================================================
// 
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

	bool font::isFont(const char *filename, int pointSize)
	{
		return name.compare(filename) == 0 && size == pointSize;
	}
}