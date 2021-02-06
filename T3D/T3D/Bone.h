// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Bone.h
//
// Bone class used for animation in conjunction with the Animation class
#pragma once

#include <vector>
#include "Transform.h"

namespace T3D
{
	//! \brief A rotation and position associated with a timestamp in seconds.
	struct KeyFrame
	{
		float time;
		Quaternion rotation;
		Vector3 position;
	};

	//! \brief Bones manage a collection of `KeyFrame`s associated with a named `Transform`, updating the `Transform` recursively every tick.
	class Bone
	{
	public:
		//! \brief Create a `Bone`.
		Bone(void) = default;

		//! \brief Destroy a `Bone`.
		~Bone(void) = default;

		//! \brief Update the `Bone`'s position by interpolating between the current and next keyframes.
		void update(float time);

		//! \brief Add a `KeyFrame` to the `Bone`. 
		void addFrame(KeyFrame f);

		//! \brief Dump information for this `Bone` to standard output.
		void printKeyFrames();

		//! \brief The `Transform` parent this `Bone` manipulates.
		Transform* transform = NULL;

		//! \brief The collection of `KeyFrame`s associated with the Bone.
		// \note _This_ is ordered, even if keyframes can be added in arbitrary sequences.
		std::vector<KeyFrame> keyframes;
	};
}
