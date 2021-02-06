// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Texture.h
//
// Class for loading, storing and manipulating textures
#pragma once

#include <string>
#include <sdl\sdl.h>
#include <sdl\SDL_ttf.h>
#include "Colour.h"

namespace T3D
{
	//! \brief Load, store and manipulate Textures.
	/*
	 * To use a Texture on a Mesh, it must be associated with a Material. Refer to T3Dtest for a lengthier example.
	 * Textures maintain an internal surface that is not managed by a Renderer. 
	 * This surface can be manipulated arbitrarily, for example by writing text to it, or plotting pixels.
	 * 
	 */
	class Texture
	{
	public:
		//! \brief Create Texture with initialized surface.
		Texture(int width, int height, bool continuousTone = true, bool mipmap = false);

		//! \brief Create Texture with initialized surface from image file.
		Texture(std::string filename, bool continuousTone = true, bool mipmap = false);

		//! \brief Destroy Texture and free surface.
		virtual ~Texture(void);

		//! \brief Write message onto texture coordinates using a provided font.
		void writeText(int x, int y, const char *text, Colour c, TTF_Font *font);

		//! \brief Get colour from pixel coordinates on screen.
		Colour getPixel(int x, int y);

		//! \brief Write a colour to a pixel coordinate.
		void plotPixel(int x, int y, Colour c);

		//! \brief Set the surface to a uniform colour and opacity.
		void clear(Colour c);

		// Renderer handle accessors
		unsigned int getID()                { return texid; }
		void         setID(unsigned int id) { texid = id; }

		// Scalar accessors
		int getWidth()          { return image->w; }
		int getHeight()         { return image->h; }
		int getNumberOfColors() { return image->format->BytesPerPixel; }


		// Buffer accessors
		void* getPtr()            { return image->pixels; }
		SDL_Surface* getSurface() { return image; }


		// Predicates
		bool isRGB(){ return (image->format->Rmask == 0x000000FF); }
		bool getCountinuousTone() { return continuousTone; }
		bool getMipmap() { return mipmap; }

		// Other utilities.
		void createFractal(Colour low, Colour high, float roughness, bool conserveHue = false);

	private:
		SDL_Surface *image;			//! \brief Handle to SDL surface
		uint32_t texid;				//! \brief Handle to renderer texture
		bool continuousTone;		//! \brief Hint for choosing appropriate texture filtering
		bool mipmap;				//! \brief Generate automatic mipmaps when loading
	};

}
