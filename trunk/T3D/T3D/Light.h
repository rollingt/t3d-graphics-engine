// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// light.h
//
// Compnent to add lights to a game object

#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"

namespace T3D
{
	class Light :
		public Component
	{
	public:
		enum { AMBIENT, DIRECTIONAL, POINT, SPOT };

		Light(int type = AMBIENT);
		virtual ~Light(void);

		void setAmbient(float r, float g, float b, float a = 1.0){ ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a; }
		void setDiffuse(float r, float g, float b, float a = 1.0){ diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a; }
		void setSpecular(float r, float g, float b, float a = 1.0){ specular[0] = r; specular[1] = g; specular[2] = b; specular[3] = a; }

	public:
		int type;
		bool enabled;

		float ambient[4];
		float diffuse[4];
		float specular[4];
		float intensity;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
	};
}

#endif

