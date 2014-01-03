// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Standard particle controller

#ifndef PARTICLEBEHAVIOUR_H
#define PARTICLEBEHAVIOUR_H

#include "Component.h"

namespace T3D
{
	class ParticleEmitter;

	//! Standard Particle Behaviour
	/*! Manages an individual particle for its lifetime
	    Particles are reusable
	  \author  David Pentecost
	  */
	class ParticleBehaviour  :
		public Component
	{
	public:
		ParticleBehaviour(ParticleEmitter *emitter, float lifeSpanMin, float lifeSpanMax);

		virtual void start(GameObject *from);			// start or restart particle
		void stop();									// stop and hide particle
		bool isActive() { return active; }

		void setPositionRange(float distance);
		void setVelocity(Vector3 velocity, Vector3 variance);
		void setAcceleration(Vector3 accel, Vector3 variance);
		void setSpeedLimits(float min, float max);

		//void setAlphaFade(float start, float end, float duration);

		void update(float dt);

	protected:
		ParticleEmitter *emitter;

		// Current state variables
		bool active;			// particle is alive and active				
		float elapsed;			// elapsed active time
		float lifeSpan;			// current lifespan of particle
		Vector3 velocity;		// current motion
		Vector3 acceleration;	// constant acceleration

		// Initial state parameters
		float lifeSpanMin;		// minimum lifetime of active particle
		float lifeSpanMax;		// maximum lifetime of active particle
		float startMaxDistance;	// maximum start distance from emitter
		Vector3 velocityBase;	// initial base velocity (X,Y,Z per second)
		Vector3 velocityVar;	// velocity variation (+/- to velocityBase)
		Vector3 accelBase;		// base acceleration vector (X,Y,Z per second per second)
		Vector3 accelVar;		// acceleration direction variance (+/- applied to accelBase)
		float minSpeed;			// minimum speed when decelerating (units per second per second)
		float maxSpeed;			// maximum speed when accelerating


	};

}

#endif //PARTICLEBEHAVIOUR_H