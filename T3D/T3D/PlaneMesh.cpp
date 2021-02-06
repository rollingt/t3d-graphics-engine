// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// PlaneMesh.cpp
//
// Create a Mesh from a Plane representation
// Adapted from Ogre3D

#include "PlaneMesh.h"

namespace T3D
{
	PlaneMesh::PlaneMesh(int density) : density(density)
	{
		int numVerts = (density+1)*(density+1);
		int numTris = density*density*2;
		int numQuads = 0;

		initArrays(numVerts, numTris, numQuads);

		for (int i=0; i<=density; i++){
			for (int j=0; j<=density; j++){
				setVertex(i,j,float(i)/float(density)-0.5f,0,float(j)/float(density)-0.5f);
			}
		}

		int face = 0;
		for (int i=0; i<density; i++){
			for (int j=0; j<density; j++){
				setTriFace(face++, i*(density+1)+j, i*(density+1)+j+1, (i+1)*(density+1)+j);
				setTriFace(face++, (i+1)*(density+1)+j, i*(density+1)+j+1, (i+1)*(density+1)+j+1);
			}
		}

		checkArrays();

		// COLORS
		for (int i=0; i<numVerts; i++){
			setColor(i,1,1,1,1);
		}

		// NORMALS
		calcNormals();
		
		// UVS
		calcUVPlaneXZ();
	}

		
	void PlaneMesh::setVertex(int i, int j, float x, float y, float z){
		vertices[(i*(density+1)+j)*3] = x;
		vertices[(i*(density+1)+j)*3+1] = y;
		vertices[(i*(density+1)+j)*3+2] = z;
	}

	Vector3 PlaneMesh::getVertex(int i, int j){
		return Vector3(vertices[(i*(density+1)+j)*3], vertices[(i*(density+1)+j)*3+1], vertices[(i*(density+1)+j)*3+2]);
	}

}
