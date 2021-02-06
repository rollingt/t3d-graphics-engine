// Author: David Pentecost
//
// ParticleGravity.h
//
// A simple particle that applies gravity to a velocity for the particles lifespace
#pragma once

#include "Vector3.h"
#include "ParticleBehaviour.h"

namespace T3D
{
	class ParticleGravity :
		public ParticleBehaviour
	{
	public:
		// \brief Initialise Particle.
		/*
		 * \param emitter		Parent emitter
		 * \param initvelocity	Start velocity
		 * \param gravity		Gravity acceleration, in meters per second^2.
		 * \param lifespan		How long particle lives, in seconds
		 *
		 * \note Particles start fully opaque (i.e. alpha(Start|End) == 1.0f)
		 */
		ParticleGravity(ParticleEmitter *emitter, Vector3 initVelocity, float gravity, float lifeSpan) :
			ParticleBehaviour(emitter),
			elapsed          (0),
			initVelocity     (initVelocity),
			velocity         (initVelocity),
			gravity          (gravity),
			lifeSpan         (lifeSpan),
			alphaStart       (1.0f),
			alphaEnd         (1.0f) { }


		// \brief Set alpha blending range. 
		/*
		 * \param start Start, in seconds
		 * \param end End, in seconds
		 */
		void setAlphaFade(float start, float end);	// alpha fading from start to end of lifespan

		// \brief Start particle activity sequence.
		virtual void start(Transform *from);

		// \brief Tick particle.
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

