// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// Font.h
//
// This is a very simple wrapper around TTF_Font for use by the cache
#pragma once

#include <string>
#include <sdl\SDL_ttf.h>

namespace T3D {

	//! \brief Font class wrapping SDL's TTF_Font.
	class font
	{
	private:
		TTF_Font *ttf;
		std::string name;
		int size;

	public:
		//! \brief Create font given a name and size
		font(const char *filename, int pointSize);

		//! \brief Destroy font
		~font(void);

		//! \brief Comparison helper used by `FontCache` -- checks if a font matches a family and size
		bool matches_family_and_size(const char *filename, int pointSize);

		TTF_Font *getFont() { return ttf; }

	};

}
