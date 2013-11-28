#include "SweepPath.h"

namespace T3D{

	SweepPath::SweepPath(void)
	{
	}


	SweepPath::~SweepPath(void)
	{
	}

	Transform SweepPath::operator[](int index) const{
		return path[index];
	}

	void SweepPath::addTransform(Transform &t){
		path.push_back(t);
	}

}