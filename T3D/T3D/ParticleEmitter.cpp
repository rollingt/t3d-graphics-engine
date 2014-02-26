// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleEmitter.cpp
//
// Particle emitter and controller
// This is a generic particle creator that can be used with any particles that have the
// ParticleBehaviour component.

#include <stdlib.h>

#include "Math.h"
#include "GameObject.h"
#include "Renderer.h"
#include "T3DApplication.h"
#include "Transform.h"
#include "ParticleEmitter.h"
#include "ParticleBehaviour.h"
#include "Camera.h"
#include "Billboard.h"


namespace T3D
{
	/*! Constructor
	  Default constructor for emitter
	  \param particleCount		maximum number of active particles
	  \param startCount			number of particles alive when starting system
	  \param rampUpDuration		duration (seconds) to from startEmitRate to emitRate
	  \param startEmitrate		initial emit rate (particles/second)
	  \param duration			duration of particle emit at normal rate
	  \param emitRate			normal emit rate
	  \param rampDownDuration	winding down duration from normal to end emit rate
	  \param endEmitRate		emit rate at end
	  \param emitVariability	random variability in emit rate (0.1 is +/- 10% variability)
	  */
	ParticleEmitter::ParticleEmitter(float rampUpDuration, float startEmitRate,
		float runDuration, float emitRate, float rampDownDuration, float endEmitRate, float emitVariability)
	{
		elapsed = 0;
		emitted = 0;
	
		this->rampUpDuration = rampUpDuration;
		this->startEmitRate = startEmitRate;
		this->runDuration = runDuration;
		this->emitRate = emitRate;
		this->rampDownDuration = rampDownDuration;
		this->endEmitRate = endEmitRate;
		this->emitVariability = emitVariability;

	}

	/*! Destructor
	  */
	ParticleEmitter::~ParticleEmitter()
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			// NOTE: delete gameObjects by deleting their Transform
			delete particles[i]->gameObject->getTransform();		
		}
	}

	/*! addParticle
	  Adds a particle to the system for use. Particles would normally be added
	  immediately following the creation of the particle system.
	  \param particle		particle to add (through its ParticleBehaviour component)
	  \param start			start immediately rather than going into available pool
	  */
	void ParticleEmitter::addParticle(ParticleBehaviour *particle, bool start)
	{
		particles.push_back(particle);

		if (start) {
			particle->start(this->gameObject);
		}
		else {
			particle->stop();	// particle will be added to particlesInactive
		}
	}

	/*! setParticle
	  Adds particle to inactive list for reuse
	  IMPORTANT: This is intended only to be used by particles
	  to add themselves back into the inactive list for reuse
	  \param particle		particle to add to inactive
	  */
	void ParticleEmitter::addInactiveList(ParticleBehaviour *particle)
	{
		particlesInactive.push(particle);
	}

	/*! createBillboardParticles
	  Creates particles using Billboard as a base
	  \param n				number of particles to create
	  \param lifeSpanMin	minimum lifespan of particles (seconds)
	  \param lifeSpanMax	maximum lifespan of particles (seconds)
	  \param imageFileName	filename for billboard texture
	  \param				billboard size scaling
	  \param parent			parent Transform for particles
	  */
	void ParticleEmitter::createBillboardParticles(int n, float lifeSpanMin, float lifeSpanMax, Material *material, float scale, Transform *parent)
	{
		Transform *cameraTransform = this->gameObject->getApp()->getRenderer()->camera->gameObject->getTransform();

		for (int i=0; i<n; i++)
		{
			GameObject *particle = new GameObject(this->gameObject->getApp());

			Billboard *bbComponent = new Billboard(cameraTransform, true);
			particle->addComponent(bbComponent);
			
			ParticleBehaviour *behaviour = new ParticleBehaviour(this, lifeSpanMin, lifeSpanMax);
			particle->addComponent(behaviour);

			particle->setMaterial(material);
			particle->getTransform()->setLocalScale(Vector3(scale, scale, scale));
			particle->getTransform()->setParent(parent);
			particle->getTransform()->name = "particle";

			addParticle(behaviour, false);
		}

	}

	/*! setPositionRange
	  set initial maximum random distance for all particles from emitter
	  \param dx		maximum initial distance from particle emitter in X axis (+/-)
	  \param dy		maximum initial distance from particle emitter in Y axis (+/-)
	  \param dz		maximum initial distance from particle emitter in Z axis (+/-)
	  */
	void ParticleEmitter::setPositionRange(float dx, float dy, float dz)
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			particles[i]->setPositionRange(dx, dy, dz);
		}
	}

	/*! setDirection
	  Sets base direction of motion and random variance for particles
	  Assumes bases direction is along +ve x axis
	  \param theta_y	rotation around y axis
	  \param theta_z	rotation around z axis
	  \param variance	+/- random variation applied to angles
	  */
	void ParticleEmitter::setDirection(float theta_y, float theta_z, float variance)
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			particles[i]->setDirection(theta_y, theta_z, variance);
		}
	}

	/*! setStartVelocity
	  Sets startup seed range for all particles
	  \param min		min start speed (units per second)
	  \param max		max start speed
	  */
	void ParticleEmitter::setStartVelocity(float min, float max)
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			particles[i]->setStartVelocity(min, max);
		}
	}

	/*! setAcceleration
	  Sets particles acceleration and min or max speed for all particles
	  \param acceleration	particle acceleration (units per second per second)
	  \param speedMinax		min speed if -ve acceleration otherwise max speed
	  */
	void ParticleEmitter::setAcceleration(float acceleration, float speedMinMax)
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			particles[i]->setAcceleration(acceleration, speedMinMax);
		}
	}

	/*! setAlphaFade
	  Sets alpha blending (fade) gradient from start to end
	  of article lifecycle for all particles.
	  \param start		start alpha value (1.0 opaque, 0.0 invisible) 
	  \param max		end alpha value
	  */
	void ParticleEmitter::setAlphaFade(float start, float end)
	{
		for (unsigned int i=0; i<particles.size(); i++)
		{
			particles[i]->setAlphaFade(start, end);
		}
	}


	/*! stop
	  Stop particle system (moves elapsed time to full duration)
	  \param clear	stop and hide all active particles immediately
	  */
	void ParticleEmitter::stop(bool clear)
	{
		elapsed = rampUpDuration + runDuration + rampDownDuration;

		if (clear)
		{
			for (unsigned int i=0; i<particles.size(); i++)
			{
				// stop any active particles
				if (!particles[i]->isActive())
					particles[i]->stop();	// note this will add particle to particlesInactive
			}
		}

	}

	/*! update
	  emit particles
	  \param n		number of particles to emit
	  \param count	add to total emitted count
	  */
	void ParticleEmitter::emit(int n, bool count)
	{
		ParticleBehaviour *particle;

		while (n > 0 && !particlesInactive.empty())
		{
			particle = particlesInactive.front();
			particlesInactive.pop();		// remove from inactive list
			particle->start(this->gameObject);

			if (count) emitted++;

			n--;
		}
	}

	/*! update
	  regular system update, generate particles as required
	  \param dt	elapsed time since last frame
	  */
	void ParticleEmitter::update(float dt)
	{
		float count;
		std::list<ParticleBehaviour *>::iterator i;

		elapsed += dt;			// total particle system run time

		if (elapsed < (rampUpDuration + runDuration + rampDownDuration))
		{
			// Get expected particles for initial ramp up
			count = emitRamp(startEmitRate, emitRate, rampUpDuration, elapsed, emitVariability);
			// Plus particles for constant run (using the acceleration ramp even though constant rate)
			count += emitRamp(emitRate, emitRate, runDuration, elapsed - rampUpDuration, emitVariability);
			// Plus particles for ramp down
			count += emitRamp(emitRate, endEmitRate, rampDownDuration, elapsed - rampUpDuration- runDuration, emitVariability);

			//std::cout << "expected particles for time " << elapsed << " is " << count << ", particles emitted so far " << emitted << std::endl;

			// count is now the total number of particles (with some random variability) that should have
			// been generated by this time in the particles systems life. 
			count -= emitted;	// minus the number already emitted to give how many we need to emit now

			emit((int)(count + 0.5f), true);			// emit rounded up output count
		}
	}

	/*! emitRamp
	  get total expected particle count for a time position along an acceleration ramp
	  no particles emitted for negative
	  \param start		particles per second
	  \param end		particles per second
	  \param duration	duration of ramp
	  \param time		time pos (no particles if < 0 or max particles if > duration)
	  \param			random varaibility (+/- fraction)
	  */
	float ParticleEmitter::emitRamp(float start, float end, float duration, float time, float variability)
	{
		float accel;		// calculated acceration rate for ramp
		float count;		// expected number of particles produced to the given time

		if (time < 0 || duration <= 0) return 0;		// not in ramp or no ramp

		if (time > duration) time = duration;	// clamp time to max duration of ramp

		accel = (end - start) / duration;		// particles per second per second
		count = start * time + (accel * time * time) / 2.0f;
		count += count * (Math::randRange(0, variability*2) - variability);

		return count;
	}



}