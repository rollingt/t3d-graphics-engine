#include "material.h"

namespace T3D{
	Material::Material(void)
	{
		setDiffuse(1,1,1,1);
		setSpecular(1,1,1,1);
		setEmissive(0,0,0,1);
		shininess = 100;

		textured = false;
		texture = NULL;
		textureScale = 1.0;

		shader = NULL;

		smooth = true;

		sortedDraw = false;
		disableDepth = false;
	}

	Material::Material(float r, float g, float b, float a)
	{
		setDiffuse(r,g,b,a);
		setSpecular(1,1,1,1);
		setEmissive(0,0,0,1);
		shininess = 100;

		textured = false;
		texture = NULL;
		textureScale = 1.0;

		smooth = true;

		sortedDraw = false;
		disableDepth = false;
	}


	Material::~Material(void)
	{
	}
}
