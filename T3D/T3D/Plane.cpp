// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// plane.cpp
//
// Represents a 3D plane
// Adapted from Ogre3D

#include "Plane.h"
#include "Matrix3x3.h"

namespace T3D
{
	//-----------------------------------------------------------------------
	Plane::Plane ()
	{
		normal = Vector3(0,0,0);
		d = 0.0;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Plane& other)
	{
		normal = other.normal;
		d = other.d;
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vector3& n, float dist)
	{
		normal = n;
		d = -dist;
	}
	//---------------------------------------------------------------------
	Plane::Plane (float a, float b, float c, float d)
		: normal(a, b, c), d(d)
	{
	}
	//-----------------------------------------------------------------------
	Plane::Plane (const Vector3& p0, const Vector3& p1,
		const Vector3& p2)
	{		
		Vector3 edge1 = p1 - p0;
		Vector3 edge2 = p2 - p0;
		normal = edge1.cross(edge2);
		normal.normalise();
		d = -normal.dot(p0);
	}
	//-----------------------------------------------------------------------
	float Plane::getDistance (const Vector3& p) const
	{
		return normal.dot(p) + d;
	}
	//-----------------------------------------------------------------------
	Plane::Side Plane::getSide (const Vector3& p) const
	{
		float distance = getDistance(p);

		if ( distance < 0.0 )
			return Plane::NEGATIVE_SIDE;

		if ( distance > 0.0 )
			return Plane::POSITIVE_SIDE;

		return Plane::NO_SIDE;
	}
	//-----------------------------------------------------------------------
	Vector3 Plane::projectVector(const Vector3& p) const
	{
		// We know plane normal is unit length, so use simple method
		Matrix3x3 xform;
		xform[0][0] = 1.0f - normal.x * normal.x;
		xform[0][1] = -normal.x * normal.y;
		xform[0][2] = -normal.x * normal.z;
		xform[1][0] = -normal.y * normal.x;
		xform[1][1] = 1.0f - normal.y * normal.y;
		xform[1][2] = -normal.y * normal.z;
		xform[2][0] = -normal.z * normal.x;
		xform[2][1] = -normal.z * normal.y;
		xform[2][2] = 1.0f - normal.z * normal.z;
		return xform * p;

	}
	//-----------------------------------------------------------------------
    void Plane::normalise(void)
    {
        float len = normal.length();

        // Will also work for zero-sized vectors, but will change nothing
        if (len > 1e-08f)
        {
            float invLength = 1.0f / len;
            normal *= invLength;
            d *= invLength;
        }
    }

	//-----------------------------------------------------------------------
	std::ostream& operator<< (std::ostream& o, const Plane& p)
	{
		o << "Plane(normal=" << p.normal << ", d=" << p.d << ")";
		return o;
	}
}
