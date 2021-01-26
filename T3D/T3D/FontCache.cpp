// =========================================================================================
// 
// =========================================================================================
//
// Author: David Pentecost
//
// FontCache.h
//
// SDL ttf font manager to allow reuse of loaded fonts

#include <iostream>
#include "FontCache.h"

namespace T3D{

	// Get font from cache or load as required.
	// returns NULL if font not available
	font *FontCache::getFont(const char *filename, int pointSize)
	{
		// check the cache in case font is loaded
		for (auto &font: fonts)
		{
			if (font->matches_family_and_size(filename, pointSize)) return font;				
		}

		// try to load the font -- NULL if unable to load
		auto *maybe_font = new font(filename, pointSize);
		if (maybe_font) 
		{
			fonts.push_back(maybe_font);
		} 
		else
		{
			// TODO(Evan): Log!
		}

		return maybe_font;
	}

}
