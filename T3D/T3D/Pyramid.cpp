#include "Pyramid.h"

T3D::Pyramid::Pyramid(int size)
{
	// Init vertex and index arrays
	initArrays(4 * 6,	// num vertices
		0,		// num tris
		6);		// num quads

// Set vertices

	int pos = 0;
	//front
	setVertex(pos++, -size, -size, -size);
	setVertex(pos++, size, -size, -size);
	setVertex(pos++, size, size, -size);
	setVertex(pos++, -size, size, -size);
	//back
	setVertex(pos++, -size, -size, size);
	setVertex(pos++, size, -size, size);
	setVertex(pos++, size, size, size);
	setVertex(pos++, -size, size, size);
	//left
	setVertex(pos++, -size, -size, -size);
	setVertex(pos++, -size, size, -size);
	setVertex(pos++, -size, size, size);
	setVertex(pos++, -size, -size, size);
	//right
	setVertex(pos++, size, -size, -size);
	setVertex(pos++, size, size, -size);
	setVertex(pos++, size, size, size);
	setVertex(pos++, size, -size, size);
	//bottom
	setVertex(pos++, -size, -size, -size);
	setVertex(pos++, -size, -size, size);
	setVertex(pos++, size, -size, size);
	setVertex(pos++, size, -size, -size);
	//top
	setVertex(pos++, -size, size, -size);
	setVertex(pos++, -size, size, size);
	setVertex(pos++, size, size, size);
	setVertex(pos++, size, size, -size);

	// Build quads
	pos = 0;
	//front
	setFace(pos++, 3, 2, 1, 0);
	//back
	setFace(pos++, 4, 5, 6, 7);
	//left
	setFace(pos++, 11, 10, 9, 8);
	//right
	setFace(pos++, 12, 13, 14, 15);
	//bottom
	setFace(pos++, 19, 18, 17, 16);
	//top
	setFace(pos++, 20, 21, 22, 23);

	// Check vertex and index arrays
	checkArrays();

	// Calculate normals
	calcNormals();
}
