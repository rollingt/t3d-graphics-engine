// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Particle emitter and controller

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <list>
#include <queue>
#include "Component.h"
#include "ParticleBehaviour.h"


namespace T3D
{
	class ParticleBehaviour;

	//! Standard Particle Emitter
	/*! The particle emitter generates and lauches reusable particles s
	  \author  David Pentecost
	  */
	class ParticleEmitter :
		public Component
	{
	friend class ParticleBehaviour;
	public:
		ParticleEmitter(float duration, float startRate, float emitRate, float endRate,
			float startUpTime, float windDownTime);
		virtual ~ParticleEmitter();

		void addParticle(ParticleBehaviour *particle, bool start);	// add particle to pool
		void emit(int n);
		void stop(bool clear);
		void restart() { emitted = 0;  elapsed = 0; }				// restart from time 0

		void update(float dt);

	private:
		void addInactiveList(ParticleBehaviour *particle);	// only particles should call this!

	protected:
		std::vector<ParticleBehaviour *> particles;			// all particles
		std::queue<ParticleBehaviour *> particlesInactive;	// inactive particles that can be reused

		float elapsed;					// elapsed time

		float duration;					// total run time (particle emission stops when this reached)

		int emitted;					// number of particles emitted, excluding those from emit(n)

		float startRate;				// particles per second at time 0
		float emitRate;					// normal particles per second emit rate
		float endRate;					// particles per second when duration time reached

		float rampUpDuration;			// ramp up time from startRate to emitRate
		float rampDownDuration;			// wind down time from emitRate to endRate
	
	private:
		float emitRamp(float start, float end, float duration, float time, float variability);

	};

}

#endif //PARTICLEEMITTER_H
