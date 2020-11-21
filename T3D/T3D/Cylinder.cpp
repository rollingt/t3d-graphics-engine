#include "Cylinder.h"
#include "Math.h"

T3D::Cylinder::Cylinder(float radious, float height, int density)
{
	

	// Init vertex and index arrays
	initArrays((density*2)+((density+1)*2),	// num vertices
		density*2,		// num tris
		density);		// num quads

	float dTheta = Math:: TWO_PI / density;
	float theta;

	//init vertices for the sides 
	for (int i = 0; i < density; i++)
	{
		theta = i * dTheta;
		float x = radious * cos(theta);
		float z = radious * sin(theta);
		// top vertex 
		setVertex(i, x, height, z);
		// bottom vertex 
		setVertex(density + i, x, -height, z);
	}
	//setting up side faces using above vertices 
	for (int i = 0; i < density; i++) {
		setFace(i,//face id 
			i, //current top vertex
			(i+1) % density, //next top vertex(wrapping)
			density + (i + 1) % density,//next bottom vertex(wrapping)			
			density + 1//current bottom vertex
		);
	}
	//init vertices for the caps
	for (int i = 0; i < density; i++)
	{
		theta = i * dTheta;
		float x = radious * cos(theta);
		float z = radious * sin(theta);
		// top vertex 
		setVertex((i+(2*density)), x, height, z);
		// bottom vertex 
		setVertex(((density*3) + i), x, -height, z);
	}
	//init centre vertex for cap triangles 
	// top vertex 
	setVertex(density*4, 0, height, 0);
	// bottom vertex 
	setVertex((density * 4)+1, 0, -height, 0);
	
	//setting up cap faces using above vertices 
	for (int i = 0; i < density; i++) {
		//one for the top
		setFace(i,//face id 
			i+(density*2), //current top vertex
			((i+1) % density) + (density*2), //next top vertex(wrapping)
			density * 4//centre vertex
		);
		//one for the bottom 
		setFace(i + density,//face id 
			i + (density * 3), //current bottom vertex
			((i + 1) % density) + (density * 3), //next bottom vertex(wrapping)
			(density * 4) + 1 
		);
	}
	
	// Check vertex and index arrays
	checkArrays();

	// Calculate normals
	calcNormals();			
}
