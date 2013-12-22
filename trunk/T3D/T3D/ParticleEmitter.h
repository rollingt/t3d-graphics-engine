// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: David Pentecost
//
// ParticleEmitter.h
//
// Particle emitter and controller

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <list>
#include "ParticleBehaviour.h"


namespace T3D
{
	//! Standard Particle Emitter
	/*! The particle emitter generates and lauches reusable particles s
	  \author  David Pentecost
	  */
	class ParticleEmitter
	{
	public:
		ParticleEmitter(int particleCount, int startCount, float startEmitRate, float endEmitRate, float duration);

	protected:
		std::list<ParticleBehaviour *> particlesPool;	// particles avaiable for use
		std::list<ParticleBehaviour *> particlesActive;	// live particles
		int particleCount;								// total particle count

		//unsigned int    particleCount;					// the total number of particles
		unsigned int	aliveAtStart;					// the number of particles alive when the system is inited
		bool			shuttingDown;					// set true to prevent new births
		
		float			minLifeSpan;					// minimum time a particle can live
		float			maxLifeSpan;					// maximum time a particle can live
		
		float			minBirthSize;					// smallest size of a particle when it is created
		float			maxBirthSize;					// largest size of a particle when it is created
		float			maxSize;						// maximum size a particle can be
		
		float			minBirthSpeed;					// minimum speed of a particle when created
		float			maxBirthSpeed;					// maximum speed of a particle when created
		float			minMaxSpeed;					// (least) maximum speed a particle can have
		float			maxMaxSpeed;					// (greatest) maximum speed a particle can have
		
		float			newParticlesToEmit;				// no. of particles to emit during a single animate call
		float			birthRate;						// no. of new particles emitted per second
														
		bool			acceleration;					// acceleration switch
		//vectr			accelerationVectr;				// acceleration vector
		
		bool			useAlpha;						// controls blending mode (add/blend)
		
		int             framesWide;						// sub-image arrangement in the texture
		int             framesHigh;
			
	
	};

}

#endif //PARTICLEEMITTER_H