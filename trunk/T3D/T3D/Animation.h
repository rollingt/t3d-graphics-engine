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
		Animation(int frames, float duration);
		virtual ~Animation();
		
		virtual void update(float dt);

		void addBone(std::string n);
		void addKey(std::string n, int frame, Quaternion rot, Vector3 pos);
		void interpolate();

		void play(){ time = 0; playing = true; }
		void pause(){ playing = false; }
		void loop(bool loop){ looping = loop; } 

		void printFrames()
        {
            std::cout << "Animation:\n";
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				std::cout << "bone: " << it->first << "\n";
				Bone *b = it->second;
				b->printFrames();
			}
        }

		void printKeyFrames()
        {
            std::cout << "Animation:\n";
			BoneMap::iterator it;
			for (it = bones.begin(); it!= bones.end(); it++){
				std::cout << "bone: " << it->first << "\n";
				Bone *b = it->second;
				b->printKeyFrames();
			}
        }

	protected:
		BoneMap bones;
		float duration;
		int frames;

		float time;
		bool playing;
		bool looping;
	};
}

#endif

