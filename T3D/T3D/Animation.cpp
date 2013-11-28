#include "animation.h"
#include "GameObject.h"
#include "Math.h"

namespace T3D
{
	Animation::Animation(int frames, float duration) : frames(frames), duration(duration)
	{
		time = 0;
		looping = false;
		playing = false;
	}


	Animation::~Animation(void)
	{
	}

	void Animation::addKey(std::string n, int frame, Quaternion rot, Vector3 pos){
		BoneMap::iterator it = bones.find(n);

		if(it == bones.end())
		{
		   addBone(n);
		}

		KeyFrame f = {frame,rot,pos};
		bones[n]->keyframes.push_back(f);
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

	void Animation::interpolate(){
		BoneMap::iterator it;
		for (it = bones.begin(); it!= bones.end(); it++){
			Bone *b = it->second;
			b->interpolate(frames);
		}
	}

	void Animation::update(float dt){
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
		float frame = time/duration * (frames-1);
		
		BoneMap::iterator it;
		for (it = bones.begin(); it!= bones.end(); it++){
			Bone *b = it->second;
			b->update(frame);
		}
	}
}
