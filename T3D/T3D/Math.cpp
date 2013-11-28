// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// math.cpp
//
// Currently just a few constants
// Adapted from Ogre3D

#include <math.h>
#include "Math.h"

namespace T3D
{
    const float Math::PI = float( 4.0 * atan( 1.0 ) );
    const float Math::TWO_PI = float( 2.0 * PI );
    const float Math::HALF_PI = float( 0.5 * PI );
	const float Math::DEG2RAD = PI / float(180.0);
	const float Math::RAD2DEG = float(180.0) / PI;
	const float Math::LOG2 = log(float(2.0));

	
	float** Math::generateFractal(int size, float low, float high, float roughness, bool tile){
		float** data;
		data = new float*[size+1];
		for (int x=0; x<size+1; x++){
			data[x] = new float[size+1];
		}

		if (tile) {
			data[0][0] = (low + high)/2;		
			data[0][size] = (low + high)/2;		
			data[size][0] = (low + high)/2;		
			data[size][size] = (low + high)/2;		
		} else {	
			data[0][0] = Math::randRange(low,high);		
			data[0][size] = Math::randRange(low,high);
			data[size][0] = Math::randRange(low,high);
			data[size][size] = Math::randRange(low,high);
		}

		int step = size;

		while (step>1){
			float rough = roughness * float(step)/float(size) * (high-low);
			for (int x=0; x<size; x+=step){				
				for (int y=0; y<size; y+=step){
					data[x][y+step/2] = Math::clamp((data[x][y] + data[x][y+step])/2.0 + Math::randRange(-rough,rough),low,high);
					data[x+step/2][y] = Math::clamp((data[x][y] + data[x+step][y])/2.0 + Math::randRange(-rough,rough),low,high);
					data[x+step/2][y+step/2] = Math::clamp((data[x][y] + data[x][y+step] + data[x+step][y] + data[x+step][y+step])/4.0
						+ Math::randRange(-rough,rough),low,high);
				}
			}
			if (tile) {				
				for (int x=0; x<size; x+=step){	
					data[x+step/2][size] = data[x+step/2][0];
				}
				for (int y=0; y<size; y+=step){	
					data[size][y+step/2] = data[0][y+step/2];
				}
			} else {
				for (int x=0; x<size; x+=step){	
					data[x+step/2][size] = Math::clamp((data[x][size] + data[x+step][size])/2.0 + Math::randRange(-rough,rough),low,high);
				}
				for (int y=0; y<size; y+=step){	
					data[size][y+step/2] = Math::clamp((data[size][y] + data[size][y+step])/2.0 + Math::randRange(-rough,rough),low,high);
				}
			}
			step = step/2;
		}

		return data;
	}
}
