// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// material.h
//
// Stores material properties for an object

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

namespace T3D
{
	class Material
	{
	public:
		Material(void);
		Material(float r, float g, float b, float a);
		virtual ~Material(void);

		void setDiffuse(float r, float g, float b, float a){ diffuse[0] = r;  diffuse[1] = g; diffuse[2] = b; diffuse[3] = a; }
		void setSpecular(float r, float g, float b, float a){ specular[0] = r;  specular[1] = g; specular[2] = b; specular[3] = a; }
		void setEmissive(float r, float g, float b, float a){ emissive[0] = r;  emissive[1] = g; emissive[2] = b; emissive[3] = a; }
		void setShininess(float s){ shininess = s; }

		bool isTextured(){ return textured; }
		unsigned int getTexID(){ return texture->getID(); }
		void setTexture(Texture *tex, float scale = 1.0){ texture = tex; textured = true; textureScale = scale; }
		Texture* getTexture(){ return texture; }
		void setTextureScale(float s){ textureScale = s; }
		float getTextureScale(){ return textureScale; }

		float* getDiffuse(){ return diffuse; }
		float* getSpecular(){ return specular; }
		float* getEmissive(){ return emissive; }
		float getShininess(){ return shininess; }

	private:
		float diffuse[4];
		float specular[4];
		float shininess;
		float emissive[4];

		bool textured;
		Texture *texture;
		float textureScale;
	};
}

#endif

