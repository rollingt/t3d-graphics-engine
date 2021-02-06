// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Animation.cpp
//
// A component for controlling rigid skeletal animation.

#include "Animation.h"
#include "GameObject.h"
#include "Math.h"
#include "Logger.h"

namespace T3D
{
	/*!
	 * \param duration The maximum time of the animation
	 *
	 * \note Does not start playing or looping by default!
	 */
	Animation::Animation(float duration) : duration(duration),
										   time(0),
										   looping(false),
										   playing(false) { }

	/*!
	 * Integrates the change in time from the current keyframe to the next.
	 * \param dt Change in time
	 */
	void Animation::update(float dt){		
		if (!playing) return;

		time += dt;
		if (time > duration) {
			if (looping) {
				time = fmod(time, duration);
			} else {
				time = duration;
				playing = false;
			}
		}
		for (auto &bone: bones){
			bone.second->update(time);
		}
	}

	/*!
	 * \param n Name of the transform to add the bone to
	 *
	 * \note Issues a warning if a child Transform with name `n` does not exist 
	 */
	void Animation::addBone(std::string n)
	{
		auto parent = gameObject->getTransform()->getAncestorByName(n);
		if (parent) {
			auto bone = new Bone();
			bone->transform = parent;
			bones.insert(BoneEntry(n, bone));

			logger::Log(priority::Tracing, output_stream::File, category::Animation, "Added bone to parent %s", n.c_str());
		} else {
			logger::Log(priority::Warning, output_stream::All, category::Animation, "Bone not found in addBone: %s", n.c_str());
		}
	}

	/*!
	 * Positions in between each timestep are linearly interpolated, and orientations are spherically interpolated.
	 *
	 * \param n Name of `Transform` 
	 * \param time Time in seconds 
	 * \param pos Orientation at `time`
	 * \param pos Local position at `time`
	 *
	 * \note This will issue a warning if the time provided is outside the animation range; it will *not* clamp the time.
	 */
	void Animation::addKey(std::string n, float time, Quaternion rot, Vector3 pos){
		if (time > duration)
		{
			logger::Log(priority::Warning, 
						output_stream::All, 
						category::Animation, 
						"Keyframe %s has time [%.3fs], which is outside animation duration [%.3fs]!",
						n.c_str(),
						time,
						duration);
		}

		/* If there's no string key associated with the bone, add it to the map first,
		   otherwise std::map operator[] will insert default constructed (empty) key with the bone */
		if (bones.find(n) == bones.end()) addBone(n);

		bones[n]->addFrame(KeyFrame { time, rot, pos });
	}

	/*!
	 * \note This requires the `logger` to be initialized at the application's beignning, e.g. outside the `WinGLApplication` loop body, to work properly.
	 */
void Animation::printFrames()
	{
		logger::Log(priority::Tracing, output_stream::Console, category::Animation, "Animation Dump");
		for (auto &bone : bones){
			logger::Log(priority::Tracing, output_stream::Console, category::Animation, "Bone : %s", bone.first.c_str());
			bone.second->printKeyFrames();
		}
	}
}
