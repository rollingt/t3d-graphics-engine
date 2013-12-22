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

#include <vector>
#include "Texture.h"

namespace T3D
{
	class GameObject;

	class Material
	{
	public:
		typedef enum {
			BLEND_NONE,				// no texture blending
			BLEND_DEFAULT,			// alpha blending (sourcd alpha=0.0 invisible, alpha=1.0 opaque)
			BLEND_ADD,				// source and destination colour added
			BLEND_MULTIPLY			// Source and Destination colour multiplied
		} blendMode;

		Material(void);
		Material(float r, float g, float b, float a);
		virtual ~Material(void);

		void setDiffuse(float r, float g, float b, float a){ diffuse[0] = r;  diffuse[1] = g; diffuse[2] = b; diffuse[3] = a; }
		void setSpecular(float r, float g, float b, float a){ specular[0] = r;  specular[1] = g; specular[2] = b; specular[3] = a; }
		void setEmissive(float r, float g, float b, float a){ emissive[0] = r;  emissive[1] = g; emissive[2] = b; emissive[3] = a; }
		void setShininess(float s){ shininess = s; }
		void setFlat() { smooth = false; }
		void setSmooth() { smooth = true; }
		void setBlending(blendMode mode) { blending = mode; }

		bool isTextured(){ return textured; }
		unsigned int getTexID(){ return texture->getID(); }
		void setTexture(Texture *tex, float scale = 1.0){ texture = tex; textured = true; textureScale = scale; }
		Texture* getTexture(){ return texture; }
		void setTextureScale(float s){ textureScale = s; }
		float getTextureScale(){ return textureScale; }

		void addToQueue(GameObject* gameObject){ renderQueue.push_back(gameObject); }
		void clearQueue(){ renderQueue.clear(); }
		std::vector<GameObject*> getQueue(){ return renderQueue; }

		float* getDiffuse(){ return diffuse; }
		float* getSpecular(){ return specular; }
		float* getEmissive(){ return emissive; }
		float getShininess(){ return shininess; }

		bool getSmoothShading() { return smooth; }
		blendMode getBlending() { return blending; }

	private:
		float diffuse[4];
		float specular[4];
		float shininess;
		float emissive[4];

		bool textured;
		Texture *texture;
		float textureScale;

		bool smooth;			// or flat shading
		blendMode blending;		// basic pixel blending

		std::vector<GameObject*> renderQueue; // TODO: Change this to a priority queue
	};
}

#endif

