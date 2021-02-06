//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Base particle behaviour.
// This is a pure virtual class from which a useable particle must be derived.

#pragma once

#include "Component.h"
#include "Transform.h"

namespace T3D
{
	class ParticleEmitter;

	//  Standard Particle Behaviour
	// Manages an individual particle for its lifetime
	//    Particles are reusable
	class ParticleBehaviour  :
		public Component
	{
	public:
		/*! Constructor
		  Initialises members
		  */
		ParticleBehaviour::ParticleBehaviour(ParticleEmitter *emitter) : emitter(emitter),
																	     active(0) { }
		bool isActive() { return active; }

		virtual void start(Transform *from) = 0;			// start or restart particle
		virtual void update(float dt) = 0;

		virtual void stop();								// stop and hide particle

	protected:
		ParticleEmitter *emitter;		// parent emitter

		bool active;			// particle is alive and active				
	};

}
