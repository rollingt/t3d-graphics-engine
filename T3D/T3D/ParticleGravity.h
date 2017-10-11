#pragma once

// Author: David Pentecost
//
// ParticleGravity.h
//
// A simple particle that applies gravity to a velocity for the particles lifespace

#include "ParticleBehaviour.h"

namespace T3D
{
	class ParticleGravity :
		public ParticleBehaviour
	{
	public:
		ParticleGravity(ParticleEmitter *emitter, Vector3 initVelocity, float gravity, float lifeSpan);

		void setAlphaFade(float start, float end);	// alpha fading from start to end of lifespan

		virtual void start(Transform *from);
		virtual void update(float dt);

	protected:
		float elapsed;			// elapsed active time
		float lifeSpan;			// lifespan of particle
		Vector3 initVelocity;	// initial velocity for reuse
		Vector3 velocity;		// current velocity (per second)
		float gravity;

		float alphaStart;		// alpha at start of lifecycle
		float alphaEnd;			// alpha at end of sequence

	};

}

