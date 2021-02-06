// Author: David Pentecost
//
// ParticleGravity.cpp
//
// A simple particle that applies gravity to a velocity for the particles lifespace

#include "GameObject.h"
#include "Transform.h"
#include "ParticleGravity.h"

namespace T3D
{
	/*!
	 * \param from	GameObject to derive world position from
	*/
	void ParticleGravity::start(Transform *from)
	{
		elapsed = 0;

		// Start at emitters position
		Vector3 position = from->getWorldPosition();
		this->gameObject->getTransform()->setWorldPosition(position);

		velocity = initVelocity;		// reset to initial velocity

		gameObject->setVisible(true);	// object is now visible
		active = true;					// and active
	}


	/* 
	 * \todo ParticleGravity's constructor could take these as default parameters, along with Gravity.
	 */
	void ParticleGravity::setAlphaFade(float start, float end)
	{
		alphaStart = start;
		alphaEnd = end;
	}

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
