#include "bone.h"

namespace T3D
{	
	bool frameCompare (KeyFrame f1, KeyFrame f2) { 
		return (f1.frame<f2.frame); 
	}

	Bone::Bone(void)
	{
	}


	Bone::~Bone(void)
	{
	}

	void Bone::interpolate(int numFrames){		
		keyframes.sort(frameCompare);
		frames.resize(numFrames);

		std::list<KeyFrame>::iterator kfi = keyframes.begin();
		KeyFrame previous = *kfi;
		int f;
		Frame newFrame = {previous.rotation,previous.position};
		// pad to first frame
		for (f=0; f<previous.frame; f++){
			frames[f] = newFrame;
		}
		//start interpolating
		kfi++;
		while (kfi!=keyframes.end()){
			while (f < kfi->frame){
				float a = float(f-previous.frame)/(kfi->frame - previous.frame);
				Quaternion rot = Quaternion::slerp(previous.rotation, kfi->rotation, a);
				Vector3 pos = Vector3::lerp(previous.position, kfi->position, a);				
				newFrame.rotation = rot; newFrame.position = pos;
				frames[f] = newFrame;
				f++;
			}
			previous = *kfi;
			kfi++;
		}
		// pad to last frame
		newFrame.rotation = previous.rotation; newFrame.position = previous.position;
		for (; f<numFrames; f++){
			frames[f] = newFrame;
		}
	}

	void Bone::update(float frame){
		int pFrame = int(floor(frame));
		int nFrame = int(ceil(frame));
		transform->setLocalPosition(Vector3::lerp(frames[pFrame].position,frames[nFrame].position,frame-pFrame));
		transform->setLocalRotation(Quaternion::slerp(frames[pFrame].rotation,frames[nFrame].rotation,frame-pFrame));
	}

	void Bone::printFrames(){
		for (unsigned int i=0; i<frames.size(); i++){
			std::cout << i << ": " << frames[i].rotation << frames[i].position << "\n";
		}
	}

	void Bone::printKeyFrames(){
		std::list<KeyFrame>::iterator kfi;
		for (kfi=keyframes.begin(); kfi!=keyframes.end(); kfi++){
			std::cout << kfi->frame << ": " << kfi->rotation << kfi->position << "\n";
		}
	}
}