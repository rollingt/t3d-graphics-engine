#include <iostream>
#include "Texture.h"
#include "Math.h"

namespace T3D
{

	Texture::Texture(int width, int height)
	{
		Uint32 rmask, gmask, bmask, amask;

		/* SDL interprets each pixel as a 32-bit number, so our masks must depend
		   on the endianness (byte order) of the machine */
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN){
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
		} else {
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
		}

		image = SDL_CreateRGBSurface(0, width, height, 32,rmask, gmask, bmask, amask);
		if(image == NULL) {
			std::cout << "CreateRGBSurface failed: %s\n" << SDL_GetError() << "\n";
		}

		texid = 0; // incorrect
	}

	Texture::Texture(std::string filename)
	{
		if ( image = SDL_LoadBMP(filename.c_str()) )
		{
			std::cout << "loaded: " << filename << "\n";
		} else {
			std::cout << "could not load: " << filename << "\n";
		}
		texid = 0; // incorrect
	}

	Texture::~Texture(void)
	{
		SDL_FreeSurface(image);
	}

	void Texture::createFractal(Colour low, Colour high, float roughness, bool conserveHue){
		int resolution = (image->w > image->h)?image->w:image->h; // use larger dimension

		if (conserveHue){
			float** data = Math::generateFractal(resolution,0,1,roughness,true); // make tileable texture

			for (int x=0; x<image->w; x++){
				for (int y=0; y<image->h; y++){
					int r = int(data[x][y]*(high.r - low.r) + low.r);
					int g = int(data[x][y]*(high.g - low.g) + low.g);
					int b = int(data[x][y]*(high.b - low.b) + low.b);
					plotPixel(x,y,Colour(r,g,b,255));
				}
			}

			
			for (int i=0; i<resolution; i++){
				delete []data[i];
			}
			delete []data;
		} else {
			float** rdata = Math::generateFractal(resolution,0,1,roughness,true);
			float** gdata = Math::generateFractal(resolution,0,1,roughness,true);
			float** bdata = Math::generateFractal(resolution,0,1,roughness,true);

			for (int x=0; x<image->w; x++){
				for (int y=0; y<image->h; y++){
					int r = int(rdata[x][y]*(high.r - low.r) + low.r);
					int g = int(gdata[x][y]*(high.g - low.g) + low.g);
					int b = int(bdata[x][y]*(high.b - low.b) + low.b);
					plotPixel(x,y,Colour(r,g,b,255));
				}
			}

			
			for (int i=0; i<resolution; i++){
				delete []rdata[i];
				delete []gdata[i];
				delete []bdata[i];
			}
			delete []rdata;
			delete []gdata;
			delete []bdata;
		}
	}
	
	Colour Texture::getPixel(int x, int y){
		return Colour(((Uint32 *)image->pixels)[x*(image->pitch/sizeof(unsigned int)) + y]); 
	}

	void Texture::plotPixel(int x, int y, Colour c){
		
		if( SDL_MUSTLOCK(image) )
			SDL_LockSurface(image);

		Uint32 colour = SDL_MapRGBA(image->format, c.r, c.g, c.b, c.a);
		Uint8 * pixel = (Uint8*)image->pixels;
		pixel += (y * image->pitch) + (x * sizeof(Uint32));
		*((Uint32*)pixel) = colour;

		
		if( SDL_MUSTLOCK(image) )
			SDL_UnlockSurface(image);
	}

	void Texture::clear(Colour c){
		Uint32 colour = SDL_MapRGBA(image->format, c.r, c.g, c.b, c.a);
		SDL_Rect all = {0,0,image->w,image->h};
		SDL_FillRect(image, &all, colour);
	}

}
