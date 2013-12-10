// =========================================================================================
// 
// =========================================================================================
//
// Author: David Pentecost
//
// Font.h
//
// This is a very simple wrapper around TTF_Font for use by the cache

#ifndef FONT_H
#define FONT_H

#include <vector>
#include <sdl\SDL_ttf.h>

namespace T3D{

	class font
	{
	private:
		TTF_Font *ttf;
		std::string name;
		int size;

	public:
		font(const char *filename, int pointSize);
		~font(void);

		bool isFont(const char *filename, int pointSize);

		TTF_Font *getFont() { return ttf; }

	};

}

#endif //FONT
