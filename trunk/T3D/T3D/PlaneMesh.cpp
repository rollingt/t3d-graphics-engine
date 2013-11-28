#include "planemesh.h"

namespace T3D{

	PlaneMesh::PlaneMesh(int density) : density(density)
	{
		numVerts = (density+1)*(density+1);
		numTris = density*density*2;
		numQuads = 0;

		vertices = new float[numVerts*3];		
		triIndices = new unsigned int[numTris*3];
		
		for (int i=0; i<=density; i++){
			for (int j=0; j<=density; j++){
				setVertex(i,j,float(i)/float(density)-0.5f,0,float(j)/float(density)-0.5f);
			}
		}

		int face = 0;
		for (int i=0; i<density; i++){
			for (int j=0; j<density; j++){
				setFace(face++, i*(density+1)+j, i*(density+1)+j+1, (i+1)*(density+1)+j);
				setFace(face++, (i+1)*(density+1)+j, i*(density+1)+j+1, (i+1)*(density+1)+j+1);
			}
		}

		// COLORS
		colors = new float[numVerts*4];
		
		for (int i=0; i<numVerts; i++){
			setColor(i,1,1,1,1);
		}

		// NORMALS
		normals = new float[numVerts*3];
		calcNormals();
		
		// UVS
		uvs = new float[numVerts*2];
		calcUVPlaneXZ();
	}


	PlaneMesh::~PlaneMesh(void)
	{
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
