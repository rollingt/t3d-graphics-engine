#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "sdl\sdl.h"
#include "Colour.h"

namespace T3D
{

	class Texture
	{
	public:
		Texture(int width, int height);
		Texture(std::string filename);
		virtual ~Texture(void);

		void createFractal(Colour low, Colour high, float roughness, bool conserveHue = false);

		int getWidth(){ return image->w; }
		int getHeight(){ return image->h; }

		Colour getPixel(int x, int y);
		void plotPixel(int x, int y, Colour c);
		void clear(Colour c);

		unsigned int getID(){ return texid; }
		void setID(unsigned int id){ texid = id; }
		
		int getNumberOfColors(){ return image->format->BytesPerPixel; }

		void* getPtr() { return image->pixels; }
		SDL_Surface* getSurface() { return image; }

		bool isRGB(){ return (image->format->Rmask == 0x000000FF); }

	private:
		SDL_Surface *image;
		unsigned int texid;
	};

}

#endif

