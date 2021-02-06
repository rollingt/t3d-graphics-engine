// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Particle emitter and controller
#pragma once

#include <vector>
#include <queue>

#include "Component.h"
#include "ParticleBehaviour.h"

namespace T3D
{
	class ParticleBehaviour;

	//! \brief Generate reusable particles.
	class ParticleEmitter :
		public Component
	{
	public:
		// \brief Create Particle emitter
		ParticleEmitter(float duration, 
						float startRate, 
						float emitRate, 
						float endRate,
						float startUpTime, 
						float windDownTime) :
			duration(duration),
			startRate(startRate),
			emitRate(emitRate),
			endRate(endRate),
			rampUpDuration(startUpTime),
			rampDownDuration(windDownTime),
			emitted(0),
			elapsed(0) { }

		// \brief Deletes all particles
		virtual ~ParticleEmitter();

		// \brief Adds a particle to the available pool.
		void addParticle(ParticleBehaviour *particle, bool start);

		// \brief Emit `n` particles immediatel	y
		void emit(uint32_t n);											

		// \brief Stop particle system
		void stop(bool clear);

		// \brief Restart timer
		void restart() { emitted = 0;  elapsed = 0; }				

		// \brief Tick particle system
		void update(float dt);

	protected:
		// \brief Set of all particles.
		std::vector<ParticleBehaviour *> particles;

		// \brief Inactive particles that can be reused.
		std::queue<ParticleBehaviour *> particlesInactive;

		float elapsed;					// elapsed time

		float duration;					// total run time (particle emission stops when this reached)

		int emitted;					// number of particles emitted, excluding those from emit(n)

		float startRate;				// particles per second at time 0
		float emitRate;					// normal particles per second emit rate
		float endRate;					// particles per second when duration time reached

		float rampUpDuration;			// ramp up time from startRate to emitRate
		float rampDownDuration;			// wind down time from emitRate to endRate
	
	private:
		// \brief Adds particle to inactive list for reuse
		void addInactiveList(ParticleBehaviour *particle);	// only particles should call this!
		// \brief Calculate expected particles at a timestep
		float emitRamp(float start, float end, float duration, float time, float variability);

	//! Need to maanage the members of ParticleBehaviour component instances.
	friend class ParticleBehaviour;

	};

}
