// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// FontCache.h
//
// SDL ttf font manager to allow reuse of loaded fonts

#include "FontCache.h"
#include "Logger.h"

namespace T3D{

	/*
	 * \param filename Where the file is, as a relative path.
	 * \param pointSize Font size. Differs per family, but 16 or so should be good.
	 *
	 * \note Returns `nullptr` if the font doesn't exist, and a diagnostic message is output to the console and log file.
	 */
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
			logger::Log(priority::Warning, 
						output_stream::All,
						category::Platform,
						"Font creation failed!");
		}

		return maybe_font;
	}

}
