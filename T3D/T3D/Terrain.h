#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include "component.h"
#include "Vector3.h"

namespace T3D{

	///-------------------------------------------------------------------------------------------------
	/// @class	Terrain
	///
	/// @brief	Generates a terrain mesh.
	///
	/// @author	Rollingt
	/// @date	2/10/2013

	class Terrain :
		public Component
	{
	public:
		Terrain();
		virtual ~Terrain(void);

		float getHeight(Vector3 pos);

		void createTerrain(std::string tex, float horizScale, float vertScale);
		void createFractalTerrain(int resolution, float horizScale, float vertScale, float roughness);

		float size;
		float gridSize;
	};

}

#endif

