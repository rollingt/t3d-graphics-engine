//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Base particle behaviour.
// This is a pure virtual class from which a useable particle must be derived.

#include "GameObject.h"
#include "Math.h"
#include "ParticleEmitter.h"
#include "ParticleBehaviour.h"


namespace T3D
{
	/*! Constructor
	  Initialises members
	  */
	ParticleBehaviour::ParticleBehaviour(ParticleEmitter *emitter)
	{
		this->emitter = emitter;
	}


	/*! stop
	  stop and hide particle
	  */
	void ParticleBehaviour::stop()
	{
		gameObject->setVisible(false);
		active = false;
		// notify parent this particle is no longer active
		emitter->addInactiveList(this);
	}

}