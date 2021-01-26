#include "Sweep.h"

namespace T3D
{

	/*! Constructs a mesh from a (usually 2D) profile by sweeping the profile along a SweepPath
		\param points		The points defining the profile
		\param path		Defines the path to sweep along
		\param closed		If true, the last profile along the path will be connected back to the first profile
		*/
	Sweep::Sweep(std::vector<Vector3> &profilePoints, SweepPath &path, bool closed) : Mesh()
	{
		/* Add an extra step to the sweep path if its closed */
		if (closed) 
		{
			path.addTransform(path[0]);
		}

		// MSVC cannot inline `size()` calls for a vector that is mutable, as its possible
		// for the size to change during a loop body.
		// So, grab the sizes here and use them throughout the rest of the function as we know they don't change.
		const uint32_t pointsInPath      = path.size();
		const uint32_t verticesInProfile = profilePoints.size();

		int numVerts = pointsInPath * verticesInProfile;
		int numQuads = numVerts;

			       /* triangles not used */
		initArrays(numVerts, 0, numQuads);
		
		int vpos = 0;
		int fpos = 0;

		for (uint32_t i = 0; i < pointsInPath; i++){
			for(uint32_t j = 0; j < verticesInProfile; j++)
			{
				Vector3 v = path[i].transformPoint(profilePoints[j]);
				setVertex(vpos++,v.x,v.y,v.z);

				setQuadFace(fpos++,
							( (j + 0)                      + (i + 0)                  * verticesInProfile),
							(((j + 1) % verticesInProfile) + (i + 0)                  * verticesInProfile),
							(((j + 1) % verticesInProfile) + ((i + 1) % pointsInPath) * verticesInProfile),
							( (j + 0)                      + ((i + 1) % pointsInPath) * verticesInProfile));
			}
		}

		checkArrays();
		calcNormals();		
		
		int pos = 0;
		for (int i=0; i<numVerts; i++){
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
	}

}
