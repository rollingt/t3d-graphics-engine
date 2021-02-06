//
// Author: David Pentecost
//
// ParticleEmitter.cpp
//
// Base particle behaviour.

#include "GameObject.h"
#include "ParticleEmitter.h"
#include "ParticleBehaviour.h"

namespace T3D
{
	/*! 
	 * Stops a particle. Sets the GameObject to invisible and notifies parent of inactivity.
	 */
	void ParticleBehaviour::stop()
	{
		gameObject->setVisible(false);
		active = false;
		// notify parent this particle is no longer active
		emitter->addInactiveList(this);
	}

}
