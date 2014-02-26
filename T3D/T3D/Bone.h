// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Bone.h
//
// Bone class used for animation in conjunction with the Animation class

#ifndef BONE_H
#define BONE_H

#include <vector>
#include <list>
#include "Transform.h"

namespace T3D
{
	struct KeyFrame
	{
		float time;
		Quaternion rotation;
		Vector3 position;
	};

	class Bone
	{
	public:
		Bone(void);
		~Bone(void);

		void interpolate(int numFrames);
		void update(float time);

		void addFrame(KeyFrame f);

		void printFrames();
		void printKeyFrames();

		Transform* transform;
		std::vector<KeyFrame> keyframes;
	};
}

#endif

