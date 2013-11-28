#ifndef BONE_H
#define BONE_H

#include <vector>
#include <list>
#include "Transform.h"

namespace T3D
{
	struct Frame
	{
		Quaternion rotation;
		Vector3 position;
	};

	struct KeyFrame
	{
		int frame;
		Quaternion rotation;
		Vector3 position;
	};

	class Bone
	{
	public:
		Bone(void);
		~Bone(void);

		void interpolate(int numFrames);
		void update(float frame);

		void printFrames();
		void printKeyFrames();

		Transform* transform;
		std::list<KeyFrame> keyframes;
		std::vector<Frame> frames;
	};
}

#endif

