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

	FontCache::FontCache(void)
	{
	}

	FontCache::~FontCache(void)
	{
		font *entry;
		std::vector<font *>::iterator i;
		for (i = fonts.begin(); i != fonts.end(); i++)
		{
			entry = *i;
			delete entry;
		}
	}

	// Get font from cache or load as required
	// returns NULL if font not available
	font *FontCache::getFont(const char *filename, int pointSize)
	{
		font *entry;
		std::vector<font *>::iterator i;

		// find font
		for (i = fonts.begin(); i != fonts.end(); i++)
		{
			entry = *i;
			if (entry->isFont(filename, pointSize))
				return entry;				// found matching font for reuse
		}

		entry = new font(filename, pointSize);

		fonts.push_back(entry);
		return entry;
	}

}