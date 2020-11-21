#include "Pyramid.h"

T3D::Pyramid::Pyramid(int size)
{
	// Init vertex and index arrays
	initArrays(16,	// num vertices
		4,		// num tris
		1);		// num quads

// Set vertices

	int pos = 0;
	//front
	setVertex(pos++, 0, 0, 0);
	setVertex(pos++, (size/2), (size / 2), (size / 2));
	setVertex(pos++, size, 0, 0);
	//setVertex(pos++, -size, size, -size);
	//back
	setVertex(pos++, 0, 0, size);
	setVertex(pos++, (size/2), (size/2), (size/2));
	setVertex(pos++, size, 0, size);
	//setVertex(pos++, -size, size, size);
	//left
	setVertex(pos++, 0, 0, 0);
	setVertex(pos++, (size / 2), (size / 2), (size / 2));
	setVertex(pos++, 0, 0, size);
	//setVertex(pos++, -size, -size, size);
	//right
	setVertex(pos++, size, 0, 0);
	setVertex(pos++, (size / 2), (size / 2), (size / 2));
	setVertex(pos++, size, 0, size);
	//setVertex(pos++, size, -size, size);
	//bottom
	setVertex(pos++, 0, 0, 0);
	setVertex(pos++, size, 0, 0);
	setVertex(pos++, 0, 0, size);
	setVertex(pos++, size, 0, size);
	//top
	//setVertex(pos++, -size, size, -size);
	//setVertex(pos++, -size, size, size);
	//setVertex(pos++, size, size, size);
	//setVertex(pos++, size, size, -size);

	// Build triangles
	pos = 0;
	//front
	setFace(pos++, 2, 1, 0);
	//back
	setFace(pos++, 5,4,3);
	//left
	setFace(pos++, 8,7,6);
	//right
	setFace(pos++, 11,10,9);
	
	// Build square
	
	//bottom
	setFace(pos++,15, 14,13,12);	
	

	// Check vertex and index arrays
	checkArrays();

	// Calculate normals
	calcNormals();
}
