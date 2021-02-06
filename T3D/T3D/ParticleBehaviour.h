//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Base particle behaviour.
// This is a pure virtual class from which a useable particle must be derived.

#pragma once

#include "Component.h"

namespace T3D
{
	class Transform;
	class ParticleEmitter;

	//! \brief Component to add Particle behaviour to a GameObject. Created from a parent ParticleEmitter. 
	/* ParticleBehaviour manages an individual particle for its lifetime.
	 * Particles are also reusable.
	 */

	class ParticleBehaviour  :
		public Component
	{
	public:
		// \brief Create ParticleBehaviour, initialising members
		ParticleBehaviour::ParticleBehaviour(ParticleEmitter *emitter) : emitter(emitter),
																	     active(false) { }
		virtual void start(Transform *from) = 0;		// start or restart particle
		virtual void update(float dt) = 0;				// tick particle system
		virtual void stop();							// stop and hide particle

		bool isActive() { return active; }

	protected:
		ParticleEmitter *emitter;		// parent emitter

		bool active;			// particle is alive and active
	};

}
