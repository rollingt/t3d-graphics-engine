// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// sphere.cpp
//
// A simple sphere mesh with variable size and polygon density

#include <math.h>
#include "sphere.h"
#include "Math.h"
#include <iostream>

namespace T3D{

	Sphere::Sphere(float radius, int density)
	{
		numVerts = density*(density-1)+2;

		// VERTICES

		vertices = new float[numVerts*3];

		int pos=0;

		float dPhi = Math::PI/density;
		float dTheta = (float)2.0f*Math::PI/density;
		
		for (int i=1; i<density; i++){
			float phi = i*dPhi;
			float r = sin(phi)*radius;
			float y = cos(phi)*radius;

			for (int j=0; j<density; j++){
				float theta = j*dTheta;
				float x = r* cos(theta);
				float z = r*sin(theta);
				setVertex((i-1)*density + j,x,y,z);
			}
		}
		setVertex(density*(density-1),0,-radius,0);
		setVertex(density*(density-1)+1,0,radius,0);
		
		// COLORS
		colors = new float[numVerts*4];
		
		for (int i=0; i<numVerts; i++){
			setColor(i,1,1,1,1);
		}

		// FACES
		numTris = density*2+density*(density-2)*2;
		
		triIndices = new unsigned int[numTris*3];
		
		int face = 0;
		//top and bottom
		for (int j=0; j<density; j++){
			setFace(face++, density*(density-1)+1,(j+1)%density,j);
			setFace(face++, density*(density-1), density*(density-2)+j, density*(density-2) + (j+1)%density);
		}

		//rest
		for (int i=1; i<density-1; i++){
			for (int j=0; j<density; j++){
				setFace(face++, (i-1)*density + j, (i-1)*density + (j+1)%density, i*density + j);
				setFace(face++, (i-1)*density + (j+1)%density, i*density + (j+1)%density, i*density + j);
			}
		}
		
		// NORMALS
		normals = new float[numVerts*3];
		calcNormals();
		
		uvs = new float[numVerts*2];
		calcUVSphere();
	}


	Sphere::~Sphere(void)
	{
	}

}
