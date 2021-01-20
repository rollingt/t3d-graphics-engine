// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Animation.cpp
//
// A component for controlling skeletal animation.

#include "animation.h"
#include "GameObject.h"
#include "Math.h"

namespace T3D
{
	// Create an animation of length `duration`. 
	// Does _not_ play or loop by default.
	Animation::Animation(float duration) : duration(duration),
										   time(0),
										   looping(false),
										   playing(false) { }


	// Adds a named keyframe describing a rotation and position beginning at a provided timestep.
	// NOTE(Evan): This is incorrect if the provided time is outside the animation's range.
	//             Should this be clamped to the animation's range and logged?
	void Animation::addKey(std::string n, float time, Quaternion rot, Vector3 pos){
		BoneMap::iterator it = bones.find(n);

		if(it == bones.end())
		{
		   addBone(n);
		}

		KeyFrame f = {time,rot,pos};
		bones[n]->addFrame(f);
	}

	// Adds a bone to the parent game object.
	void Animation::addBone(std::string n)
	{
		Bone *b = new Bone();
		b->transform = gameObject->getTransform()->getAncestorByName(n);
		if (b->transform!=NULL){
			bones.insert(BoneEntry(n,b));
		} else {
			std::cout << "ERROR: bone not found in addBone(" << n << ")\n)";
		}
	}

	// Integrate the change in time `dt` to the animation's state.
	// Looping animations are reset to the beginning, and non-looping animations are flagged as finished.
	void Animation::update(float dt){		
		if (playing){
			time += dt;
			if (time>duration){
				if (looping){
					while (time>duration)
						time = time-duration;
				} else {
					time = duration;
					playing = false;
				}
			}
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				Bone *b = it->second;
				b->update(time);
			}
		}
	}
}
