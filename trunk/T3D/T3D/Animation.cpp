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
	Animation::Animation(float duration) : duration(duration)
	{
		time = 0;
		looping = false;
		playing = false;
	}


	Animation::~Animation(void)
	{
	}

	void Animation::addKey(std::string n, float time, Quaternion rot, Vector3 pos){
		BoneMap::iterator it = bones.find(n);

		if(it == bones.end())
		{
		   addBone(n);
		}

		KeyFrame f = {time,rot,pos};
		bones[n]->addFrame(f);
	}

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
