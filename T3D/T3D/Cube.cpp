// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// cube.cpp
//
// Simple cube mesh with coloured sides
// Note that faces are triangles only and that normals are repeated for each vertex
// This allows use of gl array pointers

#include "Cube.h"

namespace T3D
{
	Cube::Cube(float size)
	{
		// Init vertex and index arrays
		initArrays(4 * 6,	// num vertices
			       0,		// num tris
			       6);		// num quads

		// Set vertices

		int pos=0;
		//front
		setVertex(pos++,-size,-size,-size);
		setVertex(pos++,size,-size,-size);
		setVertex(pos++,size,size,-size);
		setVertex(pos++,-size,size,-size);
		//back
		setVertex(pos++,-size,-size,size);
		setVertex(pos++,size,-size,size);
		setVertex(pos++,size,size,size);
		setVertex(pos++,-size,size,size);
		//left
		setVertex(pos++,-size,-size,-size);
		setVertex(pos++,-size,size,-size);
		setVertex(pos++,-size,size,size);
		setVertex(pos++,-size,-size,size);
		//right
		setVertex(pos++,size,-size,-size);
		setVertex(pos++,size,size,-size);
		setVertex(pos++,size,size,size);
		setVertex(pos++,size,-size,size);
		//bottom
		setVertex(pos++,-size,-size,-size);
		setVertex(pos++,-size,-size,size);
		setVertex(pos++,size,-size,size);
		setVertex(pos++,size,-size,-size);
		//top
		setVertex(pos++,-size,size,-size);
		setVertex(pos++,-size,size,size);
		setVertex(pos++,size,size,size);
		setVertex(pos++,size,size,-size);

		// Build quads
		pos = 0;
		//front
		setQuadFace(pos++,3,2,1,0);
		//back
		setQuadFace(pos++,4,5,6,7);
		//left
		setQuadFace(pos++,11,10,9,8);
		//right
		setQuadFace(pos++,12,13,14,15);
		//bottom
		setQuadFace(pos++,19,18,17,16);
		//top
		setQuadFace(pos++,20,21,22,23);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();	

		// Setup other arrays		
		pos = 0;
		//front
		for (int i=0; i<4; i++){
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//back
		for (int i=0; i<4; i++){
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		}
		//left
		for (int i=0; i<4; i++){
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//right
		for (int i=0; i<4; i++){
			colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		}
		//bottom
		for (int i=0; i<4; i++){
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
		//top
		for (int i=0; i<4; i++){
			colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}	

		//uvs
		pos = 0;
		for (int f = 0; f<6; f++){
			uvs[pos++] = 0; uvs[pos++] = 0; 
			uvs[pos++] = 0; uvs[pos++] = 1; 
			uvs[pos++] = 1; uvs[pos++] = 1; 
			uvs[pos++] = 1; uvs[pos++] = 0; 
		}
	}


	Cube::~Cube(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
