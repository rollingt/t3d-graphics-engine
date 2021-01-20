#include "Sweep.h"

namespace T3D
{

	/*! Constructs a mesh from a (usually 2D) profile by sweeping the profile along a SweepPath
		\param points		The points defining the profile
		\param path		Defines the path to sweep along
		\param closed		If true, the last profile along the path will be connected back to the first profile
		*/
	Sweep::Sweep(std::vector<Vector3> points, SweepPath &path, bool closed)
	{
		int numVerts = path.size()*points.size();
		int numTris = 0;
		int numQuads = 0;

		if (closed)
			numQuads = path.size()*points.size();
		else
			numQuads = (path.size()-1)*points.size();

		initArrays(numVerts, numTris, numQuads);
		
		int vpos = 0;
		int fpos = 0;
		for (unsigned int i=0; i<path.size(); i++){
			for(unsigned int j = 0; j < points.size(); j++)
			{
				Vector3 v = path[i].transformPoint(points[j]);
				setVertex(vpos++,v.x,v.y,v.z);

				if (closed || i<path.size()-1){
					setQuadFace(fpos++,(j+i*points.size()),
								   ((j+1)%points.size()+i*points.size()),
								   ((j+1)%points.size()+((i+1)%path.size())*points.size()),
								   (j+((i+1)%path.size())*points.size()));
				}
			}
		}

		checkArrays();
		
		calcNormals();		
		
		int pos = 0;
		for (int i=0; i<numVerts; i++){
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
	}

	
	//! Destructor
	Sweep::~Sweep(void)
	{
	}

}
