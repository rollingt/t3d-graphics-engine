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
#include "Component.h"
#include "ParticleBehaviour.h"


namespace T3D
{
	//! Standard Particle Emitter
	/*! The particle emitter generates and lauches reusable particles s
	  \author  David Pentecost
	  */
	class ParticleEmitter :
		public Component
	{
	public:
		ParticleEmitter(float rampUpDuration, float startEmitRate, float runDuration, float emitRate, 
			float rampDownDuration, float endEmitRate, float emitVariability);
		virtual ~ParticleEmitter();

		void addParticle(ParticleBehaviour *particle, bool start);	/// add particle for use
		void windDown() { elapsed = rampUpDuration + runDuration; }
		void restart() { elapsed = 0; emitted = 0; }
		void stop(bool clear);
		void emit(int count);
		void update(float dt);

	private:
		float emitRamp(float start, float end, float duration, float time, float variability);

	protected:
		std::list<ParticleBehaviour *> particlesPool;	// particles avaiable for use
		std::list<ParticleBehaviour *> particlesActive;	// live particles

		float elapsed;					//elapsed system time
		int emitted;					//number of particles emitted during run (not counting any started when added)

		float rampUpDuration;
		float startEmitRate;
		float runDuration;
		float emitRate;
		float rampDownDuration;
		float endEmitRate;
		float emitVariability;			// random variability in emit rate (+/- fraction)
	
	};

}

#endif //PARTICLEEMITTER_H