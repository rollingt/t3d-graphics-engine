// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// mesh.cpp
//
// Basic mesh class to store vertices, normals, colors, uvs(currently not used), and indices
// Triangle meshes only.  Unoptimised.

#include <stdlib.h>
#include "Mesh.h"
#include "Math.h"

namespace T3D
{

	Mesh::Mesh(void)
	{
		vertices = NULL;
		normals = NULL;
		triIndices = NULL;
		quadIndices = NULL;
		colors = NULL;
		uvs = NULL;
		numVerts = 0;
		numTris = 0;
		numQuads = 0;
	}

	Mesh::~Mesh(void)
	{
		if (vertices) delete []vertices;
		if (triIndices) delete []triIndices;
		if (quadIndices) delete []quadIndices;
		if (normals) delete []normals;
		if (colors) delete []colors;
		if (uvs) delete []uvs;
	}
		
	void Mesh::setVertex(int i, float x, float y, float z){
		vertices[i*3] = x;
		vertices[i*3+1] = y;
		vertices[i*3+2] = z;
	}
	Vector3 Mesh::getVertex(int i){
		return Vector3(vertices[i*3], vertices[i*3+1], vertices[i*3+2]);
	}
	void Mesh::setColor(int i, float r, float g, float b, float a){
		colors[i*4] = r;
		colors[i*4+1] = g;
		colors[i*4+2] = b;
		colors[i*4+3] = a;
	}
	Vector4 Mesh::getColor(int i){
		return Vector4(colors[i*4], colors[i*4+1], colors[i*4+2], colors[i*4+3]);
	}
	void Mesh::setNormal(int i, float x, float y, float z){
		normals[i*3] = x;
		normals[i*3+1] = y;
		normals[i*3+2] = z;
	}
	void Mesh::setNormal(int i, Vector3 n){
		normals[i*3] = n.x;
		normals[i*3+1] = n.y;
		normals[i*3+2] = n.z;
	}
	void Mesh::addNormal(int i, Vector3 n){
		normals[i*3] += n.x;
		normals[i*3+1] += n.y;
		normals[i*3+2] += n.z;
	}
	Vector3 Mesh::getNormal(int i){
		return Vector3(normals[i*3], normals[i*3+1], normals[i*3+2]);
	}
	void Mesh::setFace(int i, int a, int b, int c){
		triIndices[i*3] = a;
		triIndices[i*3+1] = b;
		triIndices[i*3+2] = c;
	}
	void Mesh::setFace(int i, int a, int b, int c, int d){
		quadIndices[i*4] = a;
		quadIndices[i*4+1] = b;
		quadIndices[i*4+2] = c;
		quadIndices[i*4+3] = d;
	}
	
	void Mesh::setUV(int i, float u, float v){
		uvs[i*2] = u;
		uvs[i*2+1] = v;
	}

	void Mesh::calcNormals(){
		// set all normals to zero
		for (int i=0; i<numVerts; i++){
			setNormal(i,0,0,0);
		}

		// add normal for all tris
		for (int i=0; i<numTris; i++){
			 Vector3 v1 = getVertex(triIndices[i*3]); 
			 Vector3 v2 = getVertex(triIndices[i*3+1]); 
			 Vector3 v3 = getVertex(triIndices[i*3+2]);
			 Vector3 normal = (v2-v1).cross(v3-v2);
			 addNormal(triIndices[i*3],normal);			 
			 addNormal(triIndices[i*3+1],normal);
			 addNormal(triIndices[i*3+2],normal);
		}

		// add normal for all quads
		for (int i=0; i<numQuads; i++){
			 Vector3 v1 = getVertex(quadIndices[i*4]); 
			 Vector3 v2 = getVertex(quadIndices[i*4+1]); 
			 Vector3 v3 = getVertex(quadIndices[i*4+2]);
			 Vector3 normal = (v2-v1).cross(v3-v2);
			 addNormal(quadIndices[i*4],normal);			 
			 addNormal(quadIndices[i*4+1],normal);
			 addNormal(quadIndices[i*4+2],normal);
			 addNormal(quadIndices[i*4+3],normal);
		}

		// normalise normals
		normalise();
	}

	void Mesh::invertNormals(){
		// set all normals to zero
		for (int i=0; i<numVerts; i++){
			Vector3 n = getNormal(i);
			setNormal(i,-n.x,-n.y,-n.z);
		}
	}

	void Mesh::calcUVSphere(){		
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			float r = sqrt(v.x*v.x+v.z*v.z);
			setUV(i,atan2f(v.x,v.z)/Math::PI+0.5f, atan2f(v.y,r)/Math::PI+0.5f);
		}
	}

	void Mesh::calcUVPlaneXY(){	
		float maxX = 0;
		float maxY = 0;
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			if (fabs(v.x)>maxX)
				maxX = fabs(v.x);
			if (fabs(v.y)>maxY)
				maxY = fabs(v.y);
		}
		
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			setUV(i,v.x/maxX/2.0f+0.5f, v.y/maxY/2.0f+0.5f);
		}
	}

	void Mesh::calcUVPlaneYZ(){
	}

	void Mesh::calcUVPlaneXZ(){
		float maxX = 0;
		float maxZ = 0;
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			if (fabs(v.x)>maxX)
				maxX = fabs(v.x);
			if (fabs(v.z)>maxZ)
				maxZ = fabs(v.z);
		}
		
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			setUV(i,v.x/maxX/2.0f+0.5f, v.z/maxZ/2.0f+0.5f);
		}
	}

	void Mesh::calcUVCube(){
	}

	void Mesh::normalise(){
		for (int i=0; i<numVerts; i++){
			Vector3 v = getNormal(i);
			v.normalise();
			setNormal(i,v);
		}
	}
}
