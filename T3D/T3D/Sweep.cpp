#include "Sweep.h"

namespace T3D
{

	Sweep::Sweep(std::vector<Vector3> points, SweepPath &path, bool closed)
	{
		numVerts = path.size()*points.size();

		if (closed)
			numQuads = path.size()*points.size();
		else
			numQuads = (path.size()-1)*points.size();


		vertices = new float[numVerts*3];
		quadIndices = new unsigned int[numQuads*4];		
		
		int vpos = 0;
		int fpos = 0;
		for (int i=0; i<path.size(); i++){
			for(int j = 0; j < points.size(); j++)
			{
				Vector3 v = path[i].transformPoint(points[j]);
				setVertex(vpos++,v.x,v.y,v.z);

				if (closed || i<path.size()-1){
					setFace(fpos++,(j+i*points.size()),
								   ((j+1)%points.size()+i*points.size()),
								   ((j+1)%points.size()+((i+1)%path.size())*points.size()),
								   (j+((i+1)%path.size())*points.size()));
				}
			}
		}		
		
		normals = new float[numVerts*3];
		calcNormals();		
		
		colors = new float[numVerts*4];
		int pos = 0;
		for (int i=0; i<numVerts; i++){
			colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		}
	}


	Sweep::~Sweep(void)
	{
	}

}
