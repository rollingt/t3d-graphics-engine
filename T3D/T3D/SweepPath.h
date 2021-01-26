
#ifndef SWEEPPATH_H
#define SWEEPPATH_H

#include <vector>
#include "Transform.h"

namespace T3D
{
	class SweepPath
	{
	public:
		SweepPath(void);
		virtual ~SweepPath(void);

		Transform operator[](int index) const;
		void addTransform(Transform &t);
		uint32_t size(){ return path.size(); }

		void makeCirclePath(float radius, int density);

	protected:
		std::vector<Transform> path;
	};
}

#endif

