// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleBehaviour.cpp
//
// Particle emitter and controller


#include "GameObject.h"
#include "Math.h"
#include "Transform.h"
#include "ParticleEmitter.h"
#include "ParticleBehaviour.h"


namespace T3D
{
	/*! Constructor
	  Initialises members
	  */
	ParticleBehaviour::ParticleBehaviour(ParticleEmitter *emitter, float lifeSpanMin, float lifeSpanMax)
	{
		this->emitter = emitter;
		this->lifeSpanMin = lifeSpanMin;
		this->lifeSpanMax = lifeSpanMax;

		active = false;

		startMaxDistance = 1;

		velocityBase = Vector3(0, 0, 0);
		velocityVar = Vector3(0, 0, 0);
		accelBase = Vector3(0, 0, 0);
		accelVar = Vector3(0, 0, 0);
		minSpeed = -1000;			// no limits
		maxSpeed = 1000;
	}


	/*! start
	  Starts particle activity sequence
	  \param from		object to derive world position from 

	  */
	void ParticleBehaviour::start(GameObject *from)			// start or restart particle
	{
		float rvalue;

		elapsed = 0;
		lifeSpan = Math::randRange(lifeSpanMin, lifeSpanMax);

		// Derive world position from gameObject of parent ParticleEmitter
		// Note the particle may or may not be a descendent of the particle emitter
		Vector3 position = from->getTransform()->getWorldPosition();
		position.x += Math::randRangeND(-startMaxDistance, startMaxDistance);
		position.y += Math::randRangeND(-startMaxDistance, startMaxDistance);
		position.z += Math::randRangeND(-startMaxDistance, startMaxDistance);
		this->gameObject->getTransform()->setWorldPosition(position);

		velocity = Vector3(velocityBase.x + Math::randRangeND(-velocityVar.x, velocityVar.x),
							velocityBase.y + Math::randRangeND(-velocityVar.y, velocityVar.y),
							velocityBase.z + Math::randRangeND(-velocityVar.z, velocityVar.z));
		acceleration = Vector3(accelBase.x + Math::randRangeND(-accelVar.x, accelVar.x),
							accelBase.y + Math::randRangeND(-accelVar.y, accelVar.y),
							accelBase.z + Math::randRangeND(-accelVar.z, accelVar.z));

		gameObject->setVisible(true);
		active = true;
	}

										// 

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


	/*! setPositionRange
	  set initial maximum random distance from emitter
	  \param distance		maximum initial distance from particle emitter
	  */
	void ParticleBehaviour::setPositionRange(float distance)
	{
		startMaxDistance = distance; 
	}


	/*! setVelocity
	  Sets base velocity and random variation for particle motion
	  \param velocity		base veolcity vector (added to position per second) 
	  \param variance		+/- random variation applied to velocity
	  */
	void ParticleBehaviour::setVelocity(Vector3 velocity, Vector3 variance)
	{
		velocityBase = velocity;
		velocityVar = variance;
	}

	/*! setAcceleration
	  Sets acceleration vector and random variance
	  \param accel		base acceleration (added to velocity per second)
	  \param variance	random variance in direction of acceleration (+/-)
	  */
	void ParticleBehaviour::setAcceleration(Vector3 accel, Vector3 variance)
	{
		accelBase = accel;
		accelVar = variance;
	}

	/*! setSpeedLimits
	  Sets minimum and maximum speed (velocity.length())
	  \param min		minimum speed 
	  \param max		maximum speed
	  */
	void ParticleBehaviour::setSpeedLimits(float min, float max)
	{
		minSpeed = min;
		maxSpeed = max;
	}

	/*! update
	  regular update
	  \param dt		elapsed time from last frame 

	  */
	void ParticleBehaviour::update(float dt)
	{
		if (active)
		{

			elapsed += dt;

			if (elapsed < lifeSpan) {

				Vector3 position = this->gameObject->getTransform()->getLocalPosition();

				velocity += acceleration * dt;

				position += velocity * dt;

				this->gameObject->getTransform()->setLocalPosition(position);

			}
			else
			{
				stop();
			}
		}

	}



}