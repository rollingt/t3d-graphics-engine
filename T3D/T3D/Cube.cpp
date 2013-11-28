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
		numVerts = 4*6;

		vertices = new float[numVerts*3];

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

		numQuads = 6;
		quadIndices = new unsigned int[numQuads*4];
		pos = 0;
		//front
		setFace(0,3,2,1,0);
		//back
		setFace(1,4,5,6,7);
		//left
		setFace(2,11,10,9,8);
		//right
		setFace(3,12,13,14,15);
		//bottom
		setFace(4,19,18,17,16);
		//top
		setFace(5,20,21,22,23);

		numTris = 0;
		
		normals = new float[numVerts*3];
		calcNormals();		
		
		colors = new float[numVerts*4];
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
		uvs = new float[numVerts*2];
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
