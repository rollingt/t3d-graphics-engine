// Author: David Pentecost
//
// ParticleGravity.cpp
//
// A simple particle that applies gravity to a velocity for the particles lifespace


#include "GameObject.h"
#include "Math.h"
#include "Transform.h"
#include "ParticleGravity.h"

namespace T3D
{
	// Constructor
	ParticleGravity::ParticleGravity(ParticleEmitter *emitter, Vector3 initVelocity, float gravity, float lifeSpan) : ParticleBehaviour(emitter)
	{
		this->elapsed = 0;

		this->initVelocity = initVelocity;
		this->velocity = initVelocity;
		this->gravity = gravity;
		this->lifeSpan = lifeSpan;

		this->alphaStart = 1.0f;
		this->alphaEnd = 1.0f;
	}


	/*! start
	Starts particle activity sequence
	\param from		object to derive world position from

	*/
	void ParticleGravity::start(Transform *from)			// start or restart particle
	{
		elapsed = 0;

		// Start at emitters position
		Vector3 position = from->getWorldPosition();
		this->gameObject->getTransform()->setWorldPosition(position);

		velocity = initVelocity;		// reset to initial velocity

		gameObject->setVisible(true);	// object is now visible
		active = true;					// and active
	}


	// setAlphaFade
	// Sets alpha blending (fade) gradient from start to end
	// of particle lifespan.
	void ParticleGravity::setAlphaFade(float start, float end)
	{
		alphaStart = start;
		alphaEnd = end;
	}

	// update
	// regular update
	//   param dt		elapsed (delta) time from last frame
	void ParticleGravity::update(float dt)
	{
		if (active)		// particle is alive and running in particle system?
		{
			elapsed += dt;

			if (elapsed < lifeSpan) {
				velocity.y += gravity * dt;		// apply gravity to velocity

				// Apply velocity to position
				Vector3 position = this->gameObject->getTransform()->getLocalPosition();
				position += velocity * dt;		// apply velocity
				this->gameObject->getTransform()->setLocalPosition(position);

				// interpolate alpha blending value
				float alpha = alphaEnd + (lifeSpan - elapsed) / lifeSpan * (alphaStart - alphaEnd);
				this->gameObject->setAlpha(alpha);

			}
			else
			{
				stop();				// end of life for this time around, particle can now be reused
			}
		}
	}
}