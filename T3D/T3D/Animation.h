// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Animation.cpp
//
// A component for controlling rigid skeletal animation.
#pragma once

#include <vector>
#include <list>
#include <string>
#include <map>

#include "Component.h"
#include "Transform.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Bone.h"

namespace T3D
{
	//! \brief The name of a Transform joint and its a Bone.
	typedef std::pair<std::string, Bone*> BoneEntry;
	//! \brief An associative container that maps the name of a Transform joint to a Bone.
	typedef std::map<std::string, Bone*> BoneMap;

	//! \brief Animation component. Ticks every frame until completion, updating a rigid skeletal hierarchy of `Bone`s associated with an `GameObject`.
	/*!
	 *	This class is just one way to implement an Animation. An alternative is to subclass `Task`, which allows for a more centralized way to manage multiple objects,
	 *  or even multiple Animations.
	 */
	class Animation :
		public Component
	{
	public:
		//! \brief Create an animation of `duration` seconds length.
		Animation(float duration);

		//! \brief Destroy the animation.
		virtual ~Animation() = default;

		//! \brief Tick the animation by integrating the change in time.
		virtual void update(float dt);

		//! \brief Adds a bone to the parent game object.
		void addBone(std::string n);

		//! \brief Adds a keyframe to a named transform, describing a rotation and position at a timestamp.
		void addKey(std::string n, float time, Quaternion rot, Vector3 pos);

		//! \brief Log all keyframes for the animation to the console.
		void printFrames();


		// Runtime helper functions. Inlined to the header because they're so small.


		//! \brief Start playing the animation, resetting its time.
		void play() { time = 0; playing = true; }

		//! \brief Pause the animation from updating. 
		void pause() { playing = false; }

		//! \brief Set the animation to loop.
		/*!
		 *
		 * \param loop New loop state
		 * \note If a non-looping animation has finished, this will effectively reset it to beginning, _then_ start playing.
		 */
		void loop(bool loop) { looping = loop; } 


	protected:
		//! \brief associative container, between named transforms and bones
		BoneMap bones;
		//! \brief how long the animation shall go for
		float   duration;
		//! \brief the animation's current time
		float   time;
		//! \brief the animation's current playing state
		bool    playing;
		//! \brief is the animation looping
		bool    looping;
	};
}
