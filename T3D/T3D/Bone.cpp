// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Bone.cpp
//
// Bone class used for animation in conjunction with the Animation class

#include "bone.h"

namespace T3D
{	
	// Add a KeyFrame to the Animation Bone. 
	// Works for arbitrary times -- Bones do not need to be declared and inserted in order.
	void Bone::addFrame(KeyFrame f){
		if (keyframes.empty()){
			keyframes.push_back(f);
		} else {			
			std::vector<KeyFrame>::iterator kfi = keyframes.begin();
			while (kfi!=keyframes.end() && f.time>(*kfi).time){
				kfi++;
			}
			keyframes.insert(kfi,f);
		}
	}
	

	// Update the Bone's position by interpolating between the current and next keyframes.
	void Bone::update(float time){
		int frame = 0;
		if (!keyframes.empty())
		{
			if (time >= keyframes[keyframes.size()-1].time) {		// reached end of sequence?
				// set to last keyframe
				transform->setLocalPosition(keyframes[keyframes.size()-1].position);
				transform->setLocalRotation(keyframes[keyframes.size()-1].rotation);
			}
			else
			{
				// find position in sequence
				while (time>=keyframes[frame].time){
					frame++;
				}
				// Set to interpolated state bequence keyframes
				float alpha = (time-keyframes[frame-1].time)/(keyframes[frame].time-keyframes[frame-1].time);
				transform->setLocalPosition(Vector3::lerp(keyframes[frame-1].position,keyframes[frame].position,alpha));
				transform->setLocalRotation(Quaternion::slerp(keyframes[frame-1].rotation,keyframes[frame].rotation,alpha));
			}
		}
	}

	// Dump information for this bone to standard output.
	void Bone::printKeyFrames(){
		std::vector<KeyFrame>::iterator kfi;
		for (kfi=keyframes.begin(); kfi!=keyframes.end(); kfi++){
			std::cout << kfi->time << ": " << kfi->rotation << kfi->position << "\n";
		}
	}
}
