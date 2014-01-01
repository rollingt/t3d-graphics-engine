// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// math.h
//
// Currently just a few constants
// Adapted from Ogre3D

#ifndef MATH_H
#define MATH_H

#include <cstdlib>
#include <algorithm>

#undef min
#undef max

namespace T3D
{

	class Math
	{
	public:
        static const float PI;
        static const float TWO_PI;
        static const float HALF_PI;
		static const float DEG2RAD;
		static const float RAD2DEG;
		static const float LOG2;

		static float lerp(float first, float second, float t){ return t*(second-first)+first; }

		static float** generateFractal(int size, float min, float max, float roughness, bool tile = false);

		/*! randRange
		  Generates a random value in a given range
		  \param minimum	range from 
		  \param maximum	range to 
		  */
		static float randRange(float minimum, float maximum){ 
			float r = float(rand())/RAND_MAX;
			return r*(maximum-minimum)+minimum; 
		}

		/*! randRangeND
		  Generates a random value in a given range with an
		  approximation of a normal distribution, uses Central
		  limit theorem.
		  \param minimum	range from 
		  \param maximum	range to 
		  \param maximum	iterations (more for better distribution curve)
		  */
		static float randRangeND(float minimum, float maximum, int iterations=3){ 
			float r = 0;
			for (int i=0; i<iterations; i++)
				r += float(rand())/RAND_MAX;
			return r / (float)iterations * (maximum - minimum) + minimum; 
		}

		static float clamp(float value, float minimum, float maximum){ 
			return std::max(
				std::min(maximum,value),minimum
				); 
		}
	};
}

#endif

