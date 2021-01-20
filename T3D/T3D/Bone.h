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
		Bone(void) = default;
		~Bone(void) = default;

		void update(float time);
		void addFrame(KeyFrame f);

		// Dump information for this bone to standard output.
		void printKeyFrames();

		// Accessed by Animation.
		Transform* transform = NULL;
		std::vector<KeyFrame> keyframes;
	};
}

#endif

