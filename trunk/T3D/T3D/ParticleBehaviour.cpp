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
#include "Quaternion.h"
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

		startDistanceX = 0;
		startDistanceY = 0;
		startDistanceZ = 0;

		dirBaseThetaY = 0.0f;
		dirBaseThetaZ = 0.0f;
		directionVar = 0.0f;
		speedStartMin = 0.0f;
		speedStartMax = 0.0f;
		acceleration = 0.0f;
		speedMinMax = 0.0f;

		alphaStart = 1.0f;
		alphaEnd = 1.0f;
	}


	/*! start
	  Starts particle activity sequence
	  \param from		object to derive world position from 

	  */
	void ParticleBehaviour::start(GameObject *from)			// start or restart particle
	{
		elapsed = 0;
		lifeSpan = Math::randRange(lifeSpanMin, lifeSpanMax);

		// Derive world position from gameObject of parent ParticleEmitter
		// Note the particle may or may not be a descendent of the particle emitter
		Vector3 position = from->getTransform()->getWorldPosition();
		position.x += Math::randRangeND(-startDistanceX, startDistanceX);
		position.y += Math::randRangeND(-startDistanceY, startDistanceY);
		position.z += Math::randRangeND(-startDistanceZ, startDistanceZ);
		this->gameObject->getTransform()->setWorldPosition(position);

		Quaternion rotQ(0.0f, dirBaseThetaY + Math::randRange(-directionVar, directionVar), 
							 dirBaseThetaZ + Math::randRange(-directionVar, directionVar));
		Matrix3x3 rotM = (Matrix3x3)rotQ;
		Vector3 unitX(1.0, 0.0, 0.0);
		direction = unitX * rotM;
		speed = Math::randRangeND(speedStartMin, speedStartMax);

				//rotationMatrix = (Matrix3x3)q;


		/*velocity = Vector3(velocityBase.x + Math::randRangeND(-velocityVar.x, velocityVar.x),
							velocityBase.y + Math::randRangeND(-velocityVar.y, velocityVar.y),
							velocityBase.z + Math::randRangeND(-velocityVar.z, velocityVar.z));
		acceleration = Vector3(accelBase.x + Math::randRangeND(-accelVar.x, accelVar.x),
							accelBase.y + Math::randRangeND(-accelVar.y, accelVar.y),
							accelBase.z + Math::randRangeND(-accelVar.z, accelVar.z));
							*/

		gameObject->setVisible(true);
		active = true;
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


	/*! setPositionRange
	  set initial maximum random distance from emitter
	  \param dx		maximum initial distance from particle emitter in X axis (+/-)
	  \param dy		maximum initial distance from particle emitter in Y axis (+/-)
	  \param dz		maximum initial distance from particle emitter in Z axis (+/-)
	  */
	void ParticleBehaviour::setPositionRange(float dx, float dy, float dz)
	{
		this->startDistanceX = dx; 
		this->startDistanceY = dy; 
		this->startDistanceZ = dz; 
	}

	/*! setDirection
	  Sets base direction of motion and random variance
	  Assumes bases direction is along +ve x axis
	  \param theta_y	rotation around y axis
	  \param theta_z	rotation around z axis
	  \param variance	+/- random variation applied to angles
	  */
	void ParticleBehaviour::setDirection(float theta_y, float theta_z, float variance)
	{
		this->dirBaseThetaY = theta_y;
		this->dirBaseThetaZ = theta_z;
		this->directionVar = variance;
	}

	/*! setStartVelocity
	  Sets startup seed range
	  \param min		min start speed (units per second)
	  \param max		max start speed
	  */
	void ParticleBehaviour::setStartVelocity(float min, float max)
	{
		this->speedStartMin = min;
		this->speedStartMax = max;
	}

	/*! setAcceleration
	  Sets particles acceleration and min or max speed
	  \param acceleration	particle acceleration (units per second per second)
	  \param speedMinax		min speed if -ve acceleration otherwise max speed
	  */
	void ParticleBehaviour::setAcceleration(float acceleration, float speedMinMax)
	{
		this->acceleration = acceleration;
		this->speedMinMax = speedMinMax;
	}

	/*! setAlphaFade
	  Sets alpha blending (fade) gradient from start to end
	  of article lifecycle.
	  \param start		start alpha value (1.0 opaque, 0.0 invisible) 
	  \param max		end alpha value
	  */
	void ParticleBehaviour::setAlphaFade(float start, float end)
	{
		alphaStart = start;
		alphaEnd = end;
	}

	/*! update
	  regular update
	  \param dt		elapsed time from last frame 

	  */
	void ParticleBehaviour::update(float dt)
	{
		float *diffuse;
		float alpha;
		Vector3 position;
		Vector3 velocity;
		float vlength;

		if (active)
		{

			elapsed += dt;

			if (elapsed < lifeSpan) {

				// Apply motion (velocity and acceleration)
				Vector3 position = this->gameObject->getTransform()->getLocalPosition();
				speed += acceleration * dt;
				// min speed if decelerating, max speed if accelerating
				if ((acceleration < 0.0f && speed < speedMinMax) || (acceleration > 0.0f && speed > speedMinMax)) {
					speed = speedMinMax;		// speed limit reached
				}
				velocity = direction * speed;
				position += velocity * dt;

				this->gameObject->getTransform()->setLocalPosition(position);

				// interpolate alpha blending value
				alpha = alphaEnd + (lifeSpan - elapsed) / lifeSpan * (alphaStart - alphaEnd);
				this->gameObject->setAlpha(alpha);

			}
			else
			{
				stop();
			}
		}

	}



}