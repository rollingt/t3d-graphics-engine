// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Bone.cpp
//
// Bone class used for animation in conjunction with the Animation class

#include "Bone.h"
#include "Logger.h"

namespace T3D
{	
	/*!
	 * Works for arbitrary times -- `Bone`s do not need to be declared and inserted in order.
	 */
	void Bone::addFrame(KeyFrame f){
		if (keyframes.empty()) {
			keyframes.push_back(f);
		} else {
			auto position = std::find_if(keyframes.begin(), 
										 keyframes.end(), 
										 [&] (KeyFrame &k) { return k.time > f.time; });
			keyframes.insert(position, f);
		}
	}
	
	void Bone::update(float time){
		if (keyframes.empty()) return;

		// If end of sequence, just use the last keyframe
		if (time >= keyframes.back().time) {
			transform->setLocalPosition(keyframes.back().position);
			transform->setLocalRotation(keyframes.back().rotation);
		}
		else
		{
			int frame = 0;
			while (time >= keyframes[frame].time){
				frame++;
			}
			auto &start = keyframes[frame - 1];
			auto &end   = keyframes[frame];

			// Set to interpolated state bequence keyframes
			float alpha = (time - start.time) / (end.time - start.time);

			transform->setLocalPosition(Vector3::lerp(start.position, end.position, alpha));
			transform->setLocalRotation(Quaternion::slerp(start.rotation, end.rotation, alpha));
		}
	}

	/*!
	 * \note This requires the application `Logger` class to be initialized to work correctly.
	 */
	void Bone::printKeyFrames() {
		for (auto &keyFrame : keyframes)
		{
			logger::Log(priority::Tracing, 
						output_stream::Console,
						category::Animation,
						"Time       :: [%.4f           m/s]        \n"
					    "\tRotation :: [%.4f           radians]    \n"
						"\tPosition :: [%.4f %.4f %.4f world space]"
						,
						keyFrame.time,
						keyFrame.rotation,
						keyFrame.position);
		}
	}
}
