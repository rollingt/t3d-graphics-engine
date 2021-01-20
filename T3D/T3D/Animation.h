// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Animation.cpp
//
// A component for controlling skeletal animation.

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include "component.h"
#include "Transform.h"
#include "Vector3.h"
#include "Bone.h"

namespace T3D
{
	typedef std::pair<std::string,Bone*> BoneEntry;
	typedef std::map<std::string,Bone*> BoneMap;

	class Animation :
		public Component
	{
	public:
		// Create an animation of length `duration`. 
		// Does not play or loop by default.
		Animation(float duration);
		virtual ~Animation() = default;
		virtual void update(float dt);

		// Adds a bone to the parent game object.
		void addBone(std::string n);

		// Adds a named keyframe describing a rotation and position beginning at a provided timestep.
		void addKey(std::string n, float time, Quaternion rot, Vector3 pos);

		// Runtime helper functions.
		void play()          { time = 0; playing = true; }
		void pause()         { playing = false;          }
		void loop(bool loop) { looping = loop;           } 

		// Log all keyframes for the animation.
		void printFrames() {
            std::cout << "Animation:\n";
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				std::cout << "bone: " << it->first << "\n";
				Bone *b = it->second;
				b->printFrames();
			}
        }

	protected:
		BoneMap bones;
		float   duration;
		float   time;
		bool    playing;
		bool    looping;
	};
}

#endif

