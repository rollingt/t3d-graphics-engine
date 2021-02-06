// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// plane.h
//
// Represents a 3D plane
// Adapted from Ogre3D
#pragma once

#include <vector>
#include "Vector3.h"

namespace T3D 
{
	// 3D plane with useful operator overloads for working with matrices and vectors.
    class Plane
    {
    public:
        /** Default constructor - sets everything to 0.
        */
        Plane ();
        Plane (const Plane& other);
        /** Construct a plane through a normal, and a distance to move the plane along the normal.*/
        Plane (const Vector3& normal, float dist);
		/** Construct a plane using the 4 constants directly **/
		Plane (float a, float b, float c, float d);
        Plane (const Vector3& normal, const Vector3& point);
        Plane (const Vector3& p0, const Vector3& p1,const Vector3& p2);

        /** The "positive side" of the plane is the half space to which the
            plane normal points. The "negative side" is the other half
            space. The flag "no side" indicates the plane itself.
        */
        enum class Side
        {
            NO_SIDE,
            POSITIVE_SIDE,
            NEGATIVE_SIDE,
            BOTH_SIDE
        };

		Plane::Side getSide (const Vector3& p) const;

        /** This is a pseudodistance. The sign of the return value is
            positive if the point is on the positive side of the plane,
            negative if the point is on the negative side, and zero if the
            point is on the plane.
            @par
            The absolute value of the return value is the true distance only
            when the plane normal is a unit length vector.
        */
        float getDistance (const Vector3& p) const;

		/** Project a vector onto the plane. 
		@remarks This gives you the element of the input vector that is perpendicular 
			to the normal of the plane. You can get the element which is parallel
			to the normal of the plane by subtracting the result of this method
			from the original vector, since parallel + perpendicular = original.
		@param v The input vector
		*/
		Vector3 projectVector(const Vector3& v) const;

        /** Normalises the plane.
            @remarks
                This method normalises the plane's normal and the length scale of d
                is as well.
            @note
                This function will not crash for zero-sized vectors, but there
                will be no changes made to their components.
        */
        void normalise(void);

		Vector3 normal;
        float d;

        /// Comparison operator
        bool operator==(const Plane& other) const
        {
            return (other.d == d && other.normal == normal);
        }
        bool operator!=(const Plane& other) const
        {
            return (other.d != d && other.normal != normal);
        }

        friend std::ostream& operator<< (std::ostream& o, const Plane& p);
    };
}
