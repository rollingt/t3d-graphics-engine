// =========================================================================================
// 
// =========================================================================================
//
// Author: David Pentecost
//
// FontCache.h
//
// SDL ttf font manager to allow reuse of loaded fonts

#ifndef FONTCACHE_H
#define FONTCACHE_H

#include <vector>
#include "Font.h"

namespace T3D{

	class FontCache
	{
	private:
		std::vector<font *> fonts;

	public:
		FontCache(void);
		~FontCache(void);

		font *getFont(const char *filename, int pointSize);
	};

}

#endif //FONTCACHE
