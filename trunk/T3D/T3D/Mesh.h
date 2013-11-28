// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// mesh.h
//
// Basic mesh class to store vertices, normals, colors, uvs(currently not used), and indices
// Triangle meshes only.  Unoptimised.

#ifndef MESH_H
#define MESH_H

#include "Component.h"
#include "Vector4.h"

namespace T3D
{
	class Mesh : public Component
	{
	public:
		Mesh(void);
		virtual ~Mesh(void);

		int getNumVerts(){
			return numVerts;
		}

		int getNumTris(){
			return numTris;
		}
		
		int getNumQuads(){
			return numQuads;
		}

		float* getVertices(){
			return vertices;
		}
		float* getNormals(){
			return normals;
		}
		float* getColors(){
			return colors;
		}
		float* getUVs(){
			return uvs;
		}
		unsigned int* getTriIndices(){
			return triIndices;
		}
		unsigned int* getQuadIndices(){
			return quadIndices;
		}

		void calcNormals();
		void invertNormals();
		void calcUVSphere();
		void calcUVPlaneXY();
		void calcUVPlaneYZ();
		void calcUVPlaneXZ();
		void calcUVCube();

		virtual void setVertex(int i, float x, float y, float z);
		virtual Vector3 getVertex(int i);
		virtual void setColor(int i, float r, float g, float b, float a);
		virtual Vector4 getColor(int i);
		virtual void setNormal(int i, float x, float y, float z);
		virtual void setNormal(int i, Vector3 n);
		virtual void addNormal(int i, Vector3 n);
		virtual void normalise();
		virtual Vector3 getNormal(int i);
		virtual void setFace(int i, int a, int b, int c);
		virtual void setFace(int i, int a, int b, int c, int d);
		virtual void setUV(int i, float u, float v);

	protected:
		int numVerts, numTris, numQuads;

		float *vertices;
		float *normals;
		float *colors;
		float *uvs;

		unsigned int *triIndices;
		unsigned int *quadIndices;
	};
}

#endif