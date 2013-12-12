#include "bone.h"

namespace T3D
{	
	bool frameCompare (KeyFrame f1, KeyFrame f2) { 
		return (f1.time<f2.time); 
	}

	Bone::Bone(void)
	{
	}


	Bone::~Bone(void)
	{
	}

	
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

	void Bone::printKeyFrames(){
		std::vector<KeyFrame>::iterator kfi;
		for (kfi=keyframes.begin(); kfi!=keyframes.end(); kfi++){
			std::cout << kfi->time << ": " << kfi->rotation << kfi->position << "\n";
		}
	}
}