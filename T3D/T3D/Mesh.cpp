// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// mesh.cpp
//
// Basic mesh class to store vertices, normals, colors, uvs(currently not used), and indices
// Unoptimised.

#include "Mesh.h"
#include "Math.h"
#include "Logger.h"

namespace T3D
{
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

	/*
	 * \note If you are reading this from a Visual Studio breakpoint, you have probably
	 * trampled adjacent memory during your mesh creation. Check the console / log file!
	 *
	 */
	Mesh::~Mesh(void)
	{
		if (vertices)    delete []vertices;
		if (triIndices)  delete []triIndices;
		if (quadIndices) delete []quadIndices;
		if (normals)     delete []normals;
		if (colors)      delete []colors;
		if (uvs)         delete []uvs;
	}

	/* 
	 * Example: If you are creating a Cube out of quads with flat shading, 
	 * you would require 24 (4 * 6) vertices, 0 tris, and 6 quads.
	 *
	 * \param numVerts Vertices required for the entire mesh. Should be exactly `(numTris * 3 + numQuads * 4)`.
	 * \param numTris Triangles required for the mesh. Can be 0 for an all-quad mesh.
	 * \param numQuads Quads required for the mesh. Can be 0 for an all-tri mesh. 
	 *
	 * \note After you initialised and filled the Mesh's buffers, you should call `calcNormals` and then `checkArrays`.
	 * \note These parameters are *unsigned*!
	 */
	void Mesh::initArrays(uint32_t numVerts, uint32_t numTris, uint32_t numQuads) {
		this->numVerts = numVerts;
		this->numTris = numTris;
		this->numQuads = numQuads;

		if (numVerts == 0)
		{
			logger::Log(priority::Warning,
						output_stream::All,
						category::Video,
						"Created a mesh with 0 vertices!");
			return; 
		}

		vertices = new float[numVerts * 3];
		for (uint32_t i = 0; i < numVerts * 3; i++) {
			vertices[i] = nanf("");
		}

		uvs = new float[numVerts * 2];
		for (uint32_t i = 0; i < numVerts * 2; i++) {
			uvs[i] = 0.0f;
		}

		normals = new float[numVerts * 3];
		for (uint32_t i = 0; i < numVerts * 3; i++) {
			normals[i] = 0.0f;
		}

		colors = new float[numVerts * 4];
		for (uint32_t i = 0; i < numVerts * 4; i++) {
			colors[i] = 1.0f;
		}

		if (numQuads > 0) {
			quadIndices = new unsigned int[numQuads * 4];
			for (uint32_t i = 0; i < numQuads * 4; i++) {
				quadIndices[i] = -1;
			}
		}
		if (numTris > 0) {
			triIndices = new unsigned int[numTris * 3];
			for (uint32_t i = 0; i < numTris * 3; i++) {
				triIndices[i] = -1;
			}
		}
	}

	bool Mesh::checkArrays() {
		if (!numVerts)
		{
			logger::Log(priority::Warning,
						output_stream::All,
						category::Video,
						"Called checkArrays() on an empty mesh!");

			return true; 
		}
		uint32_t quadIndicesMax  = numQuads ? (numQuads * 4u) - 1u : 0; /* prevent overflow */
		uint32_t triIndicesMax   = numTris  ? (numTris  * 3u) - 1u : 0; /* prevent overflow */

		bool ok = true;
		for (uint32_t i = 0; i < numVerts; i++) {
			Vector3 v = getVertex(i);
			if (isnan(v.x) || isnan(v.y) || isnan(v.z)) {
				logger::Log(priority::Warning,
							output_stream::All,
							category::Video,
							"Vertex %u has not been set!", i);
				ok = false;
			}
		}

		for (uint32_t i = 0; i < quadIndicesMax; i += 4) {
			if (quadIndices[i + 0] > numVerts ||
				quadIndices[i + 1] > numVerts || 
				quadIndices[i + 2] > numVerts || 
				quadIndices[i + 3] > numVerts)
			{
				logger::Log(priority::Warning,
							output_stream::All,
							category::Video,
							"Quad Face [%u] has not been set! Indices ::"
							"\t%3u, %3u, %3u, %3u,"
							,
							i / 4,
							quadIndices[i + 0],
							quadIndices[i + 1],
							quadIndices[i + 2],
							quadIndices[i + 3]);
				ok = false;
			}
		}


		for (uint32_t i = 0; i < triIndicesMax; i += 3) {
			if (triIndices[i + 0] > numVerts ||
				triIndices[i + 1] > numVerts || 
				triIndices[i + 2] > numVerts)
			{
				logger::Log(priority::Warning,
							output_stream::All,
							category::Video,
							"Tri Face [%u] has not been set! Indices ::"
							"\t%3u, %3u, %3u"
							,
							i / 3,
							triIndices[i + 0],
							triIndices[i + 1],
							triIndices[i + 2]);
				ok = false;
			}
		}

		return ok;
	}
		
	/*
	 * \param i Vertex to set, from `[0 ... numVerts - 1]`
	 * \param x x value
	 * \param y y value
	 * \param z z value
	 *
	 * \note Be careful to not mix up vertex counts and vertex indices, 
	 * as these are multiplied and divided out by 3 respectively.
	 */
	void Mesh::setVertex(int i, float x, float y, float z){
		vertices[i*3] = x;
		vertices[i*3+1] = y;
		vertices[i*3+2] = z;
	}

	/* 
	 * \note Be careful to not mix up vertex counts and vertex indices, as these are multiplied and divided out by 3 respectively.
	 */
	Vector3 Mesh::getVertex(int i){
		return Vector3(vertices[i*3], vertices[i*3+1], vertices[i*3+2]);
	}

	/* \note Be careful to not mix up color counts and color indices, as these are multiplied and divided out by 4 respectively.
	*/
	void Mesh::setColor(int i, float r, float g, float b, float a){
		colors[i*4] = r;
		colors[i*4+1] = g;
		colors[i*4+2] = b;
		colors[i*4+3] = a;
	}

	/* \note Be careful to not mix up color counts and color indices, as these are multiplied and divided out by 4 respectively.
	*/
	Vector4 Mesh::getColor(int i){
		return Vector4(colors[i*4], colors[i*4+1], colors[i*4+2], colors[i*4+3]);
	}

	/* \note Does not attempt to normalize these components.
	 * \note Be careful to not mix up normal counts and normal indices, as these are multiplied and divided out by 3 respectively.
	*/
	void Mesh::setNormal(int i, float x, float y, float z){
		normals[i*3] = x;
		normals[i*3+1] = y;
		normals[i*3+2] = z;
	}

	/* \note Does not check that the vector n is of unit length
	 * \note Be careful to not mix up normal counts and normal indices,  as these are multiplied and divided out by 3 respectively.
	 */
	void Mesh::setNormal(int i, Vector3 n){
		normals[i*3] = n.x;
		normals[i*3+1] = n.y;
		normals[i*3+2] = n.z;
	}

	/* \note Do not assume that the ith normal is of unit length after this call.
	 * \note Be careful to not mix up normal counts and normal indices, as these are multiplied and divided out by 3 respectively.
	*/
	void Mesh::addNormal(int i, Vector3 n){
		normals[i*3] += n.x;
		normals[i*3+1] += n.y;
		normals[i*3+2] += n.z;
	}

	/* \note Do not assume that the ith normal is of unit length after this call.
	 * \note Be careful to not mix up normal counts and normal indices, as these are multiplied and divided out by 3 respectively.
	*/
	Vector3 Mesh::getNormal(int i){
		return Vector3(normals[i*3], normals[i*3+1], normals[i*3+2]);
	}

	/* \note T3D's GLRender backend uses counter-clockwise winding order for culling.
	 * \note Be careful to not mix up vertex and triangle indices for meshes containing both types of primitive.
	 */
	void Mesh::setTriFace(int i, int a, int b, int c){
		triIndices[i*3] = a;
		triIndices[i*3+1] = b;
		triIndices[i*3+2] = c;
	}

	/* \note T3D's GLRender backend uses counter-clockwise winding order for culling.
	 * \note Be careful to not mix up vertex and quad indices for meshes containing both types of primitives.
	 */
	void Mesh::setQuadFace(int i, int a, int b, int c, int d){
		quadIndices[i*4] = a;
		quadIndices[i*4+1] = b;
		quadIndices[i*4+2] = c;
		quadIndices[i*4+3] = d;
	}
	
	// \brief Sets the ith UV index to have the components u, v.
	void Mesh::setUV(int i, float u, float v){
		uvs[i*2] = u;
		uvs[i*2+1] = v;
	}

	/*
	 * Check allocation, if you have the incorrect amount of vertices, tris or quads allocated, this function will output which are off, and by how much.
	 */
	void Mesh::checkArrayAllocation(int vert_counter, int tri_counter, int quad_counter) {
		printf("total::[vert:%d][tri:%d][quad:%d]\n", numVerts, numTris, numQuads);
		//Vertices
		if (vert_counter != numVerts) {
			if (numVerts > vert_counter) {
				printf("verts: Over-allocated by %d.\n", numVerts - vert_counter);
			}
			else {
				printf("verts: Under-allocated by %d.\n", vert_counter - numVerts);
			}
		}
		//Tris
		if (tri_counter != numTris) {
			if (numTris > tri_counter) {
				printf("tris: Over-allocated by %d.\n", numTris - tri_counter);
			}
			else {
				printf("tris: Under-allocated by %d.\n", tri_counter - numTris);
			}
		}
		//Quads
		if (quad_counter != numQuads) {
			if (numQuads > quad_counter) {
				printf("quads: Over-allocated by %d.\n", numQuads - quad_counter);
			}
			else {
				printf("quads: Under-allocated by %d.\n", quad_counter - numQuads);
			}
		}
	}

	// Calculate the normal vectors for each primitive that defines this mesh.
	// *This sets each normal to be of unit length, i.e. normalized*. 
	// It also clears memory to zero before calculating normals.
	// Note that for non-planar quads there may be lighting defects. 
	// This is especially noticable when using the Sweep class.
	void Mesh::calcNormals(){
		// set all normals to zero
		for (uint32_t i = 0; i < numVerts; i++){
			setNormal(i,0,0,0);
		}

		// add normal for all tris
		for (uint32_t i = 0; i < numTris; i++){
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
		for (uint32_t i = 0; i < numQuads; i++) {
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
			for (uint32_t j = 0; j < 4u; j++) {
				addNormal(quadIndices[i*4+j], isTri ? triNormal : normals[j]);
			}
		}

		// normalise normals
		normalise();
	}

	void Mesh::invertNormals() {
		for (uint32_t i = 0; i < numVerts; i++){
			Vector3 n = getNormal(i);
			setNormal(i,-n.x,-n.y,-n.z);
		}
	}

	// Note: To be consistent with the inheritance hierarchy, this should probably be a member function
	// of the Sphere subclass as it's not useful for all meshes.
	void Mesh::calcUVSphere() {
		for (uint32_t i = 0; i < numVerts; i++){
			Vector3 v = getVertex(i); 
			float r = sqrt(v.x*v.x+v.z*v.z);
			setUV(i,atan2f(v.x,v.z)/Math::PI+0.5f, atan2f(v.y,r)/Math::PI+0.5f);
		}
	}

	void Mesh::calcUVPlaneXY(){
		uint32_t xOffset = offsetof(Vector3, x) / sizeof(float);
		uint32_t yOffset = offsetof(Vector3, y) / sizeof(float);

		calcUVPlane(xOffset, yOffset);
	}

	void Mesh::calcUVPlaneYZ(){
		uint32_t yOffset = offsetof(Vector3, y) / sizeof(float);
		uint32_t zOffset = offsetof(Vector3, z) / sizeof(float);

		calcUVPlane(yOffset, zOffset);
	}

	void Mesh::calcUVPlaneXZ(){
		uint32_t xOffset = offsetof(Vector3, x) / sizeof(float);
		uint32_t zOffset = offsetof(Vector3, z) / sizeof(float);

		calcUVPlane(xOffset, zOffset);
	}

	/* 
	 * Given two offsets into a Vector3 representing the planes of interest, 
	 * this function will find the min and max absolute values for each plane, then calculate and set 
	 * the UVs for each vertex with respect to the min and max.
	 *
	 * \note Asserts 0 <= (vectorOffsetOne, vectorOffsetTwo) < 3.
	 * 
	 */
	void Mesh::calcUVPlane(uint32_t vectorOffsetOne, uint32_t vectorOffsetTwo)
	{
		assert(vectorOffsetOne < sizeof(Vector3) / sizeof(float));
		assert(vectorOffsetTwo < sizeof(Vector3) / sizeof(float));

		float maxP1 = 0; // Maximum for 1st plane
		float maxP2 = 0; // Maximum for 2nd plane

		for (uint32_t i = 0; i < numVerts; i++){
			Vector3 v = getVertex(i); 
			float absP1 = fabs(v[vectorOffsetOne]);
			float absP2 = fabs(v[vectorOffsetTwo]);

			maxP1 = std::max(absP1, maxP1);
			maxP2 = std::max(absP2, maxP2);
		}
		
		for (uint32_t i = 0; i < numVerts; i++){
			Vector3 v = getVertex(i); 

			float U = v[vectorOffsetOne] / maxP1 / 2.0f + 0.5f;
			float V = v[vectorOffsetTwo] / maxP2 / 2.0f + 0.5f;

			setUV(i, U, V);
		}
	}

	void Mesh::normalise() {
		for (uint32_t i=0; i<numVerts; i++){
			Vector3 v = getNormal(i);
			v.normalise();
			setNormal(i,v);
		}
	}

	// \note UNIMPLEMENTED.
	void Mesh::calcUVCube() {
		logger::Warn("Unimplemented Mesh member function `calvUVCube()` was called!");
	}
}
