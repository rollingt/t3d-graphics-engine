// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// Font.h
//
// TTF_Font wrapper for font cache

#include "Font.h"
#include "Logger.h"

namespace T3D{

	/*
	 * \param filename Where the file is, as a relative path.
	 * \param pointSize Font size. Differs per family, but 16 or so should be good.
	 */
	font::font(const char *filename, int pointSize)
	{
		name = filename;
		size = pointSize;

		ttf = TTF_OpenFont(filename, pointSize);
		if (!ttf) {
			logger::Log(priority::Warning, 
						output_stream::All,
						category::Platform,
						"TTF_OpenFont() Failed :: %s", TTF_GetError());
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
