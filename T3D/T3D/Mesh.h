// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Mesh.h
//
// Basic mesh class to store vertices, normals, colors(currently not used), uvs, and indices
// Unoptimised.
#pragma once

#include "Component.h"
#include "Vector4.h"

namespace T3D
{
	//! \brief Mesh component, stores vertices and their attributes such as normals, uvs, and indices.
	/* A Mesh is intended to be used for procedurally generated shapes, by inheriting from the Mesh class
	 * and implementing a constructor to do so. See `Cube.cpp` for an example.
	 */
	class Mesh : public Component
	{
	public:
		//! \brief Create Mesh with initialised, empty buffers.
		Mesh(void);

		//! \brief Destroy Mesh, freeing buffers.
		virtual ~Mesh(void);

		// Accessors.

		//! \brief Get number of vertices.
		int getNumVerts()    { return numVerts;    }

		//! \brief Get number of triangles.
		int getNumTris()     { return numTris;     }

		//! \brief Get number of quads.
		int getNumQuads()    { return numQuads;    }

		//! \brief Get number of vertices.
		float *getVertices()    { return vertices;    }

		//! \brief Get number of normals.
		float *getNormals()     { return normals;     }

		//! \brief Get number of colors. \note Colors isn't really used!
		float *getColors()      { return colors;      }

		//! \brief Get number of UVs.
		float *getUVs()         { return uvs;         }

		//! \brief Get a pointer to the triangle index buffer.
		uint32_t *getTriIndices()  { return triIndices;  }

		//! \brief Get a pointer to the quad index buffer.
		uint32_t *getQuadIndices() { return quadIndices; }



		//! \brief Initialises internal buffers (Vertex, Index, UV, etc) given vertex and index counts.
		void initArrays(uint32_t numVerts, uint32_t numTris, uint32_t numQuads);

		//! \brief Issue warnings to console/log file if vertex, index, uv or colour buffers contain _obviously_ uninitialized/erroneous contents.
		bool checkArrays();

		//! \brief Calculates normals for Triangles and Quads. 
		/* 
		 * \note The Mesh may contain more then numVerts after this function returns if any of the quads are nonplanar (i.e. has a curvature).
		 */
		void calcNormals();
		
		//! \brief Negates all normals (i.e. flips them facing inwards to outwards, and vice versa)
		void invertNormals();


		// Procedural texture coordinate calculations for the primitives provided by T3D.

		//! \brief Calculates UVs to wrap a spherical bounding mesh.
		void calcUVSphere();

		//! \brief Calculates UVs to wrap a XY-oriented plane.
		void calcUVPlaneXY();

		//! \brief Calculates UVs to wrap a YZ-oriented plane.
		void calcUVPlaneYZ();

		//! \brief Calculates UVs to wrap a XZ-oriented plane.
		void calcUVPlaneXZ();

		//! \brief Calculates UVs to wrap a cube. 
		void calcUVCube();

		//! \brief Sets the ith vertex to have components x, y, z.
		virtual void setVertex(int i, float x, float y, float z);

		//! \brief Returns the ith vertex.
		virtual Vector3 getVertex(int i);

		// \brief Sets the ith color to have components r, g, b, a
		virtual void setColor(int i, float r, float g, float b, float a);

		// \brief Returns the ith color.
		virtual Vector4 getColor(int i);

		// \brief Sets the ith normal to have components x, y, z.
		virtual void setNormal(int i, float x, float y, float z);

		// \brief Sets the ith normal to the vector n.
		virtual void setNormal(int i, Vector3 n);

		// \brief Adds the vector n to the ith normal.
		virtual void addNormal(int i, Vector3 n);

		// \brief Calculates and set every vertex normal to be unit length, i.e. normalized.
		virtual void normalise();

		// \brief Returns the ith normal.
		virtual Vector3 getNormal(int i);

		// \brief Sets the ith triFace to contain indices referring to vertices at positions a, b, c.
		virtual void setTriFace(int i, int a, int b, int c);

		// \brief Sets the ith quadFace to contain indices referring to vertices at positions a, b, c, d.
		virtual void setQuadFace(int i, int a, int b, int c, int d);

		//! \brief Sets the ith UV.
		virtual void setUV(int i, float u, float v);


	protected:
		//! \brief Vertex count.
		uint32_t numVerts; 

		//! \brief Triangle count. Can be 0
		uint32_t numTris;

		//! \brief Quad count. Can be 0
		uint32_t numQuads;

		//! \brief Vertex buffer. Vertices are stored packed.
		float *vertices;

		//! \brief Normal buffer.
		float *normals;

		//! \brief Colour buffer. \note Currently unused.
		float *colors;

		//! \brief UV buffer.
		float *uvs;

		//! \brief Triangle index buffer
		uint32_t *triIndices;

		//! \brief Quad index buffer
		uint32_t *quadIndices;

		//! \brief Internal helper function for calculating UV planes.
		void calcUVPlane(uint32_t vectorOffsetOne, uint32_t vectorOffsetTwo);
	};
}
