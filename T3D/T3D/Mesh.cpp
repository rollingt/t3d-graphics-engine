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
#include <stdio.h>
#include "Mesh.h"
#include "Math.h"

namespace T3D
{
	// Create a Mesh with initialised buffers and zero counts.
	Mesh::Mesh(void)
	{
		vertices    = NULL;
		normals     = NULL;
		triIndices  = NULL;
		quadIndices = NULL;
		colors      = NULL;
		uvs         = NULL;
		numVerts    = 0;
		numTris     = 0;
		numQuads    = 0;
	}

	// Delete a Mesh's buffers with non-zero counts.
	// If you are reading this from a Visual Studio breakpoint, you have probably
	// trampled base pointers in adjacent memory during your mesh creation, causing
	// the allocators delete[] buffer bookkeeping to be incorrect and it throws.
	Mesh::~Mesh(void)
	{
		if (vertices)    delete []vertices;
		if (triIndices)  delete []triIndices;
		if (quadIndices) delete []quadIndices;
		if (normals)     delete []normals;
		if (colors)      delete []colors;
		if (uvs)         delete []uvs;
	}

	// Initialises internal buffers (Vertex, Index, UV, etc) based on
	// the number of vertices the caller requires to render primitives.
	// For example, if you are creating a Cube out of Quads with flat (Gouraud) shading, 
	// you would require 24 (4 * 6) vertices, 0 tris, and 6 quads.
	void Mesh::initArrays(int numVerts, int numTris, int numQuads) {
		this->numVerts = numVerts;
		this->numTris = numTris;
		this->numQuads = numQuads;

		if (numVerts > 0) {
			vertices = new float[numVerts * 3];
			for (int i = 0; i < numVerts * 3; i++) {
				vertices[i] = nanf("");
			}

			uvs = new float[numVerts * 2];
			for (int i = 0; i < numVerts * 2; i++) {
				uvs[i] = 0.0f;
			}

			normals = new float[numVerts * 3];
			for (int i = 0; i < numVerts * 3; i++) {
				normals[i] = 0.0f;
			}

			colors = new float[numVerts * 4];
			for (int i = 0; i < numVerts * 4; i++) {
				colors[i] = 1.0f;
			}

			if (numQuads > 0) {
				quadIndices = new unsigned int[numQuads * 4];
				for (int i = 0; i < numQuads * 4; i++) {
					quadIndices[i] = -1;
				}
			}
			if (numTris > 0) {
				triIndices = new unsigned int[numTris * 3];
				for (int i = 0; i < numTris * 3; i++) {
					triIndices[i] = -1;
				}
			}
		}
	}

	// Checks all internal buffers for erroneous values, logging relevant messages.
	bool Mesh::checkArrays() {
		bool ok = true;
		for (int i = 0; i < numVerts; i++) {
			Vector3 v = getVertex(i);
			if (isnan(v.x) || isnan(v.y) || isnan(v.z)) {
				std::cout << "Vertex " << i << " has not been set\n";
				ok = false;
			}
		}

		for (int i = 0; i < numQuads; i++) {
			if (quadIndices[i * 4] < 0 || quadIndices[i * 4 + 1] < 0 || quadIndices[i * 4 + 2] < 0 || quadIndices[i * 4 + 3] < 0 ||
				quadIndices[i * 4] > numVerts-1 || quadIndices[i * 4 + 1] > numVerts - 1 || quadIndices[i * 4 + 2] > numVerts - 1 || quadIndices[i * 4 + 3] > numVerts - 1) {
				std::cout << "Quad Face " << i << " has not been set: " << quadIndices[i * 4] << "," << quadIndices[i * 4+1]<< "," << quadIndices[i * 4+2]<< "," << quadIndices[i * 4+3] << "\n";
				ok = false;
			}
		}


		for (int i = 0; i < numTris; i++) {
			if (triIndices[i * 3] < 0 || triIndices[i * 3 + 1] < 0 || triIndices[i * 3 + 2] < 0 || 
				triIndices[i * 3] > numVerts - 1 || triIndices[i * 3 + 1] > numVerts - 1 || triIndices[i * 3 + 2] > numVerts - 1) {
				std::cout << "Tri Face " << i << " has not been set: " << triIndices[i * 3] << "," << triIndices[i * 3 + 1] << "," << triIndices[i * 3 + 2] << "\n";
				ok = false;
			}
		}

		return ok;
	}
		
	// Sets the ith vertex to have components x, y, z.
	// Be careful to not mix up vertex counts and vertex indices, 
	// as these are multiplied and divided out by 3 respectively.
	void Mesh::setVertex(int i, float x, float y, float z){
		vertices[i*3] = x;
		vertices[i*3+1] = y;
		vertices[i*3+2] = z;
	}

	// Returns the ith vertex.
	// Be careful to not mix up vertex counts and vertex indices, 
	// as these are multiplied and divided out by 3 respectively.
	Vector3 Mesh::getVertex(int i){
		return Vector3(vertices[i*3], vertices[i*3+1], vertices[i*3+2]);
	}

	// Sets the ith color to have components r, g, b, a
	// Be careful to not mix up color counts and color indices, 
	// as these are multiplied and divided out by 4 respectively.
	void Mesh::setColor(int i, float r, float g, float b, float a){
		colors[i*4] = r;
		colors[i*4+1] = g;
		colors[i*4+2] = b;
		colors[i*4+3] = a;
	}

	// Returns the ith color.
	// Be careful to not mix up color counts and color indices, 
	// as these are multiplied and divided out by 4 respectively.
	Vector4 Mesh::getColor(int i){
		return Vector4(colors[i*4], colors[i*4+1], colors[i*4+2], colors[i*4+3]);
	}

	// Sets the ith normal to have components x, y, z.
	// Does not attempt to normalize these components.
	// Be careful to not mix up normal counts and normal indices, 
	// as these are multiplied and divided out by 3 respectively.
	void Mesh::setNormal(int i, float x, float y, float z){
		normals[i*3] = x;
		normals[i*3+1] = y;
		normals[i*3+2] = z;
	}

	// Sets the ith normal to the vector n.
	// Does not check that the vector n is of unit length
	// Be careful to not mix up normal counts and normal indices, 
	// as these are multiplied and divided out by 3 respectively.
	void Mesh::setNormal(int i, Vector3 n){
		normals[i*3] = n.x;
		normals[i*3+1] = n.y;
		normals[i*3+2] = n.z;
	}

	// Adds the vector n to the ith normal.
	// Do not assume that the ith normal is of unit length after this call.
	// Be careful to not mix up normal counts and normal indices, 
	// as these are multiplied and divided out by 3 respectively.
	void Mesh::addNormal(int i, Vector3 n){
		normals[i*3] += n.x;
		normals[i*3+1] += n.y;
		normals[i*3+2] += n.z;
	}

	// Returns the ith normal.
	// Do not assume these are of unit length.
	// Be careful to not mix up normal counts and normal indices, 
	// as these are multiplied and divided out by 3 respectively.
	Vector3 Mesh::getNormal(int i){
		return Vector3(normals[i*3], normals[i*3+1], normals[i*3+2]);
	}

	// Sets the ith triFace to contain indices referring to vertices at positions a, b, c.
	// It is up to you to get the winding order correct!
	// Be careful to not mix up vertex and triangle indices for meshes containing both types of primitive.
	void Mesh::setTriFace(int i, int a, int b, int c){
		triIndices[i*3] = a;
		triIndices[i*3+1] = b;
		triIndices[i*3+2] = c;
	}

	// Sets the ith quadFace to contain indices referring to vertices at positions a, b, c, d.
	// It is up to you to get the winding order correct!
	// Be careful to not mix up vertex and quad indices for meshes containing both types of primitive.
	void Mesh::setQuadFace(int i, int a, int b, int c, int d){
		quadIndices[i*4] = a;
		quadIndices[i*4+1] = b;
		quadIndices[i*4+2] = c;
		quadIndices[i*4+3] = d;
	}
	
	// Sets the ith UV index to have the components u, v.
	void Mesh::setUV(int i, float u, float v){
		uvs[i*2] = u;
		uvs[i*2+1] = v;
	}

	// Calculate the normal vectors for each primitive that defines this mesh.
	// *This sets each normal to be of unit length, i.e. normalized*. 
	// It also clears memory to zero before calculating normals.
	// Note that for non-planar quads there may be lighting defects. 
	// This is especially noticable when using the Sweep class.
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
			// normalise so that primitives of different sizes have equal weight
			 normal.normalise();
			 addNormal(triIndices[i*3],normal);			 
			 addNormal(triIndices[i*3+1],normal);
			 addNormal(triIndices[i*3+2],normal);
		}

		// add normal for all quads
		// nonplanar quads are given non-uniform normals to simulate curvature
		// quads with 3 points collinear are treated as a tri
		for (int i = 0; i < numQuads; i++) {
			Vector3 vs[4];
			for (int j = 0; j < 4; j++) {
				vs[j] = getVertex(quadIndices[i * 4 + j]);
			}
			Vector3 normals[4];
			bool isTri = false;
			Vector3 triNormal = Vector3(0.0f, 0.0f, 0.0f);
			for (int j = 0; j < 4; j++) {
				Vector3 v1 = vs[(j+3)%4];
				Vector3 v2 = vs[j];
				Vector3 v3 = vs[(j+1)%4];
				Vector3 normal = (v2 - v1).cross(v3 - v2);
				if (normal.length() > 1e-08) {
					// normalise so that primitives of different sizes have equal weight
					normal.normalise();
					normals[j] = normal;
					triNormal = normal;
				}
				else {
					isTri = true;
				}
			}
			for (int j = 0; j < 4; j++) {
				addNormal(quadIndices[i*4+j], isTri ? triNormal : normals[j]);
			}
		}

		// normalise normals
		normalise();
	}

	// Reverse the direction of each normal, i.e. if pointing 'outwards', it now points 'inwards'.
	// Preserve unit-length normals, but doesn't introduce normalization if they are not already unit length.
	void Mesh::invertNormals(){
		for (int i=0; i<numVerts; i++){
			Vector3 n = getNormal(i);
			setNormal(i,-n.x,-n.y,-n.z);
		}
	}

	// Calculate the UVs required to wrap a sphere of arbitrary density and radius.
	// NOTE(Evan): To be consistent with the inheritance hierarchy, this should probably be a member function
	// of the Sphere subclass as it's not useful for all meshes.
	void Mesh::calcUVSphere(){		
		for (int i=0; i<numVerts; i++){
			Vector3 v = getVertex(i); 
			float r = sqrt(v.x*v.x+v.z*v.z);
			setUV(i,atan2f(v.x,v.z)/Math::PI+0.5f, atan2f(v.y,r)/Math::PI+0.5f);
		}
	}

	// Calculate the UVs required to wrap an XY plane of arbitrary width and height.
	void Mesh::calcUVPlaneXY(){
		uint32_t xOffset = offsetof(Vector3, x) / sizeof(float);
		uint32_t yOffset = offsetof(Vector3, y) / sizeof(float);

		calcUVPlane(xOffset, yOffset);
	}

	// Calculate the UVs required to wrap a YZ plane of arbitrary width and height.
	void Mesh::calcUVPlaneYZ(){
		uint32_t yOffset = offsetof(Vector3, y) / sizeof(float);
		uint32_t zOffset = offsetof(Vector3, z) / sizeof(float);

		calcUVPlane(yOffset, zOffset);
	}

	// Calculate the UVs required to wrap a YZ plane of arbitrary width and height.
	void Mesh::calcUVPlaneXZ(){
		uint32_t xOffset = offsetof(Vector3, x) / sizeof(float);
		uint32_t zOffset = offsetof(Vector3, z) / sizeof(float);

		calcUVPlane(xOffset, zOffset);
	}

	// Internal helper function. Given two offsets into a Vector3 representing the planes of interest, 
	// this function will find the min and max absolute values for each plane, then calculate and set 
	// the UVs for each vertex with respect to the min and max.
	// Assumes that 0 <= (vectorOffsetOne, vectorOffsetTwo) < 3.
	void Mesh::calcUVPlane(uint32_t vectorOffsetOne, uint32_t vectorOffsetTwo)
	{
		assert(vectorOffsetOne < sizeof(Vector3) / sizeof(float));
		assert(vectorOffsetTwo < sizeof(Vector3) / sizeof(float));

		float maxP1 = 0; // Maximum for 1st plane
		float maxP2 = 0; // Maximum for 2nd plane

		for (int i = 0; i < numVerts; i++){
			Vector3 v = getVertex(i); 
			float absP1 = fabs(v[vectorOffsetOne]);
			float absP2 = fabs(v[vectorOffsetTwo]);

			maxP1 = std::max(absP1, maxP1);
			maxP2 = std::max(absP2, maxP2);
		}
		
		for (int i = 0; i < numVerts; i++){
			Vector3 v = getVertex(i); 

			float U = v[vectorOffsetOne] / maxP1 / 2.0f + 0.5f;
			float V = v[vectorOffsetTwo] / maxP2 / 2.0f + 0.5f;

			setUV(i, U, V);
		}
	}

	// Calculates and set every vertex normal to be unit length, i.e. normalized.
	void Mesh::normalise(){
		for (int i=0; i<numVerts; i++){
			Vector3 v = getNormal(i);
			v.normalise();
			setNormal(i,v);
		}
	}

	// UNIMPLEMENTED.
	void Mesh::calcUVCube(){
		printf("WARNING\n\t`calcUVCube()` is unimplemented!\n");
	}
}
