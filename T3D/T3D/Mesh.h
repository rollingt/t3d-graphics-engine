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
		// Create a Mesh with initialised buffers and zero counts.
		Mesh(void);

		// Delete a Mesh's buffers with non-zero counts.
		virtual ~Mesh(void);

		// Accessors.
		int           getNumVerts()    { return numVerts;    }
		int           getNumTris()     { return numTris;     }
		int           getNumQuads()    { return numQuads;    }
		float*        getVertices()    { return vertices;    }
		float*        getNormals()     { return normals;     }
		float*        getColors()      { return colors;      }
		float*        getUVs()         { return uvs;         }
		unsigned int* getTriIndices()  { return triIndices;  }
		unsigned int* getQuadIndices() { return quadIndices; }



		// Initialises internal buffers (Vertex, Index, UV, etc) based on
		// the number of vertices the caller requires to render primitives.
		void initArrays(uint32_t numVerts, uint32_t numTris, uint32_t numQuads);

		// Verbosely logs any vertices that are uninitialised.
		// Call this at the end of _any_ procedural mesh generation!
		bool checkArrays();

		// Calculates normals for Triangles and Quads. 
		// - Quad normals may look a bit off.
		void calcNormals();
		
		// Negates all normals (i.e. flips them facing inwards to outwards, and vice versa)
		void invertNormals();

		// Procedural texture coordinate calculations for the primitives provided by T3D.
		void calcUVSphere();
		void calcUVPlaneXY();
		void calcUVPlaneYZ();
		void calcUVPlaneXZ();
		void calcUVCube();

		virtual void    setVertex(int i, float x, float y, float z);
		virtual Vector3 getVertex(int i);
		virtual void    setColor(int i, float r, float g, float b, float a);
		virtual Vector4 getColor(int i);
		virtual void    setNormal(int i, float x, float y, float z);
		virtual void    setNormal(int i, Vector3 n);
		virtual void    addNormal(int i, Vector3 n);
		virtual void    normalise();
		virtual Vector3 getNormal(int i);
		virtual void    setTriFace(int i, int a, int b, int c);
		virtual void    setQuadFace(int i, int a, int b, int c, int d);
		virtual void    setUV(int i, float u, float v);


	protected:
		unsigned int numVerts, numTris, numQuads;

		float *vertices;
		float *normals;
		float *colors;
		float *uvs;

		unsigned int *triIndices;
		unsigned int *quadIndices;

	private:
		void calcUVPlane(uint32_t vectorOffsetOne, uint32_t vectorOffsetTwo);
	};
}

#endif
