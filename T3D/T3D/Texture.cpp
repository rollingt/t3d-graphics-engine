// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Texture.cpp
//
// Class for loading, storing and manipulating textures

#include <sdl\SDL_image.h>
#include <assert.h>

#include "Texture.h"
#include "Math.h"
#include "Logger.h"

namespace T3D
{
	Texture::Texture(int width, int height, bool continuousTone, bool mipmap)
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
		if(image == NULL) 
		{
			logger::Log(priority::Error, 
						output_stream::All, 
						category::Video, 
						"SDL_CreateRGBSurface failed :: %s\n", SDL_GetError());
		}

		this->continuousTone = continuousTone;
		this->mipmap = mipmap;

		texid = 0; // incorrect
	}

	Texture::Texture(std::string filename, bool continuousTone, bool mipmap)
	{
		if (image = IMG_Load(filename.c_str()))			// supports lots of file formats
		{
			logger::Log(priority::Tracing, output_stream::File, category::Video, "Loaded texture : %s\n", filename.c_str());
		} 
		else 
		{
			logger::Log(priority::Error, output_stream::All, category::Video, "Could not load texture : %s\n",  filename.c_str());
		}

		this->continuousTone = continuousTone;
		this->mipmap = mipmap;

		texid = 0; // incorrect
	}

	Texture::~Texture(void)
	{
		SDL_FreeSurface(image);
	}

	/*
	 * \param x	x position (leftmost)
	 * \param y y position (uppermost)
	 * \param text	message, assumed null-terminated c-string 
	 * \param c	RGBA text colour
	 * \param font handle to font family & size pair
	 *
	 * \note The origin of a Texture's surface has `y_max` at the top.
	 */
	void Texture::writeText(int         x, 
							int         y, 
							const char *text, 
							Colour      c, 
							TTF_Font   *font)
	{
		SDL_Surface *temp;
		SDL_Color color;

		color.r = c.r;
		color.g = c.g;
		color.b = c.b;
	
		/* Use SDL_TTF to render our text */
		temp = TTF_RenderText_Blended(font, text, color);
	
		SDL_Rect destRect;
		destRect.x = x;
		destRect.y = y;
		destRect.w = temp->w;
		destRect.h = temp->h;

		SDL_BlitSurface(temp, 0, image, &destRect);
	
		SDL_FreeSurface(temp);
	}
	
	/*
	 * \param x	pixel x
	 * \param y	pixel y
	 *
	 * \note Assumes `(0 > x > surface_width)`, `(0 > y > surface_height)`;
	 */
	Colour Texture::getPixel(int x, int y){
		return Colour(((Uint32 *)image->pixels)[x*(image->pitch/sizeof(unsigned int)) + y]); 
	}

	/*
	 * \param x	pixel x
	 * \param y	pixel y
	 * \param c	pixel colour
	 *
	 * \note This will crash if `(0 > x > surface_width)`, `(0 > y > surface_height)`;
	 * \note `DrawTask` provides a bounds-checked, efficient function `pushPixel` to draw many pixels onto a surface and diagnose errors.
	 */
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

	/*
	 * \param c	surface colour
	 * \note Asserts surface size is smaller than UINT16_MAX.
	 */
	void Texture::clear(Colour c){
		Uint32 colour = SDL_MapRGBA(image->format, c.r, c.g, c.b, c.a);
		assert(image->w < UINT16_MAX); // Keeps static analyzers happy.
		assert(image->h < UINT16_MAX);

		SDL_Rect all = {0, 0, uint16_t(image->w), uint16_t(image->h)};
		SDL_FillRect(image, &all, colour);
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

}
