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

		void addInactiveList(ParticleBehaviour *particle);	// only particles should call this!

		void addParticle(ParticleBehaviour *particle, bool start);	/// add particle for use
		void createBillboardParticles(int n, float lifeSpanMin, float lifeSpanMax, Material *material, float scale, Transform *parent); 

		// particle attributes
		void setPositionRange(float distance);
		void setVelocity(Vector3 velocity, Vector3 variance);
		void setAcceleration(Vector3 accel, Vector3 variance);
		void setSpeedLimits(float min, float max);

		void windDown() { elapsed = rampUpDuration + runDuration; }
		void restart() { elapsed = 0; emitted = 0; }
		void stop(bool clear);
		void emit(int n, bool count=false);
		void update(float dt);


	private:
		float emitRamp(float start, float end, float duration, float time, float variability);

	protected:
		std::vector<ParticleBehaviour *> particles;			// all particles
		std::queue<ParticleBehaviour *> particlesInactive;	// inactive particles that can be started

		float elapsed;					//elapsed system time
		int emitted;					//number of particles emitted during run

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