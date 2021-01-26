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
#include <queue>
#include "Texture.h"
#include "Shader.h"

namespace T3D
{
	class GameObject;

	class Material
	{
	public:
		enum class BlendMode 
		{
			NONE,				// no texture blending
			DEFAULT,			// alpha blending (sourcd alpha=0.0 invisible, alpha=1.0 opaque)
			ADD,				// source and destination colour added
			MULTIPLY			// Source and Destination colour multiplied
		};

		Material(void);
		Material(float r, float g, float b, float a);
		virtual ~Material(void);

		void setDiffuse(float r, float g, float b, float a){ diffuse[0] = r;  diffuse[1] = g; diffuse[2] = b; diffuse[3] = a; }
		void setSpecular(float r, float g, float b, float a){ specular[0] = r;  specular[1] = g; specular[2] = b; specular[3] = a; }
		void setEmissive(float r, float g, float b, float a){ emissive[0] = r;  emissive[1] = g; emissive[2] = b; emissive[3] = a; }
		void setShininess(float s){ shininess = s; }
		void setFlatShading() { smooth = false; }
		void setSmoothShading() { smooth = true; }
		void setBlending(BlendMode mode) { blending = mode; }

		bool isTextured(){ return textured; }
		unsigned int getTexID(){ return texture->getID(); }
		void setTexture(Texture *tex, float scale = 1.0){ texture = tex; textured = true; textureScale = scale; }
		Texture* getTexture(){ return texture; }
		void setTextureScale(float s){ textureScale = s; }
		float getTextureScale(){ return textureScale; }

		void setShader(Shader* s){ shader = s; }
		Shader* getShader(){ return shader; }

		void addToQueue(GameObject* gameObject){ renderQueue.push(gameObject); }
		std::queue<GameObject*> &getQueue(){ return renderQueue; }

		float* getDiffuse(){ return diffuse; }
		float* getSpecular(){ return specular; }
		float* getEmissive(){ return emissive; }
		float getShininess(){ return shininess; }

		bool getSmoothShading() { return smooth; }
		BlendMode getBlending() { return blending; }

		void setSortedDraw(bool sort, bool noDepthWrite) { sortedDraw = sort; disableDepth = noDepthWrite; }
		bool getSortedDraw() { return sortedDraw; }
		bool getDisablDepth() { return disableDepth; }

	private:
		float diffuse[4];
		float specular[4];
		float shininess;
		float emissive[4];

		bool textured;
		Texture *texture;
		float textureScale;

		Shader *shader;

		bool smooth;			// or flat shading
		BlendMode blending;		// basic pixel blending

		bool sortedDraw;		// requires depth sorting when drawn
		bool disableDepth;		// disables depth buffer updating (will still read)

		std::queue<GameObject*> renderQueue;
	};
}

#endif

