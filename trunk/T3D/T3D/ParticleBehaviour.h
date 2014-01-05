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

		void setPositionRange(float dx, float dy, float dz);

		void setDirection(float theta_y, float theta_z, float variance);
		void setStartVelocity(float min, float max);
		void setAcceleration(float acceleration, float speedMinMax);

		void setAlphaFade(float start, float end);

		void update(float dt);

	protected:
		ParticleEmitter *emitter;

		// Current state variables
		bool active;			// particle is alive and active				
		float elapsed;			// elapsed active time
		float lifeSpan;			// current lifespan of particle

		Vector3 direction;		// direction of motion (unit vector)
		float speed;			// current speed

		// Initial state parameters
		float lifeSpanMin;		// minimum lifetime of active particle
		float lifeSpanMax;		// maximum lifetime of active particle

		float startDistanceX;	// maximum start distance from emitter in X axis
		float startDistanceY;	// maximum start distance from emitter in Y axis
		float startDistanceZ;	// maximum start distance from emitter in Z axis

		float dirBaseThetaY;	// base direction rotation around Y axis
		float dirBaseThetaZ;	// base direction rotation around Z axis
		float directionVar;		// +/- random variability to direction theta Y,Z

		float speedStartMin;	// start speed min (units per second)
		float speedStartMax;	// start speed max (speed random between min and max)
		float acceleration;		// acceleration (units per second per second)
		float speedMinMax;		// min or max speed (based on ve of acceleration)

		float alphaStart;		// alpha at start of lifecycle
		float alphaEnd;			// alpha at end of sequence

	};

}

#endif //PARTICLEBEHAVIOUR_H