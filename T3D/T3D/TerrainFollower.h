#ifndef TERRAINFOLLOWER_H
#define TERRAINFOLLOWER_H

#include "component.h"
#include "Terrain.h"

namespace T3D{

	class TerrainFollower :
		public Component
	{
	public:
		TerrainFollower(Terrain* t, float h);
		virtual ~TerrainFollower(void);

		virtual void update(float dt);

	private:
		Terrain* terrain;
		float height;
	};
}

#endif