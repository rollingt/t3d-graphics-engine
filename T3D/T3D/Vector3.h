// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// vector3.h
//
// 3d vector class
// Adapted from Ogre3D

#ifndef VECTOR3_H
#define VECTOR3_H

#include <algorithm>
#include <iostream>
#include <assert.h>
#include <math.h>

namespace T3D
{
    class Vector3
    {
    public:
		float x, y, z;

    public:
        inline Vector3()
        {
        }

        inline Vector3( const float x, const float y, const float z )
            : x( x ), y( y ), z( z )
        {
        }

        inline explicit Vector3( const float arr[3] )
            : x( arr[0] ),
              y( arr[1] ),
              z( arr[2] )
        {
        }

        inline explicit Vector3( float* const arr )
            : x( arr[0] ), y( arr[1] ), z( arr[2] )
        {
        }


		/** Exchange the contents of this vector with another. 
		*/
		inline void swap(Vector3& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		inline float operator [] ( const int i ) const
        {
            assert( i < 3 );

            return *(&x+i);
        }

		inline float& operator [] ( const int i )
        {
            assert( i < 3 );

            return *(&x+i);
        }
		/// Pointer accessor for direct copying
		inline float* ptr()
		{
			return &x;
		}
		/// Pointer accessor for direct copying
		/*inline const float* ptr() const
		{
			return &x;
		}*/

        /** Assigns the value of the other vector.
            @param
                rkVector The other vector
        */
        inline Vector3& operator = ( const Vector3& other )
        {
            x = other.x;
            y = other.y;
            z = other.z;

            return *this;
        }

        inline bool operator == ( const Vector3& other ) const
        {
            return ( x == other.x && y == other.y && z == other.z );
        }

        inline bool operator != ( const Vector3& other ) const
        {
            return ( x != other.x || y != other.y || z != other.z );
        }

        // arithmetic operations
        inline Vector3 operator + ( const Vector3& other ) const
        {
            return Vector3(
                x + other.x,
                y + other.y,
                z + other.z);
        }

        inline Vector3 operator - ( const Vector3& other ) const
        {
            return Vector3(
                x - other.x,
                y - other.y,
                z - other.z);
        }

        inline Vector3 operator * ( const float s ) const
        {
            return Vector3(
                x * s,
                y * s,
                z * s);
        }

        inline Vector3 operator / ( const float s ) const
        {
            assert( s != 0.0 );

            float inv = 1.0f / s;

            return Vector3(
                x * inv,
                y * inv,
                z * inv);
        }

        inline const Vector3& operator + () const
        {
            return *this;
        }

        inline Vector3 operator - () const
        {
            return Vector3(-x, -y, -z);
        }

        // overloaded operators to help Vector3
        inline friend Vector3 operator * ( const float s, const Vector3& v )
        {
            return Vector3(
                s * v.x,
                s * v.y,
                s * v.z);
        }

        inline friend Vector3 operator / ( const float s, const Vector3& v )
        {
            return Vector3(
                s / v.x,
                s / v.y,
                s / v.z);
        }

        // arithmetic updates
        inline Vector3& operator += ( const Vector3& other )
        {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }

        inline Vector3& operator -= ( const Vector3& other )
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        inline Vector3& operator *= ( const float s )
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        inline Vector3& operator /= ( const float s )
        {
            assert( s != 0.0 );

            float inv = 1.0f / s;

            x *= inv;
            y *= inv;
            z *= inv;

            return *this;
        }

        /** Returns the length (magnitude) of the vector.
            @warning
                This operation requires a square root and is expensive in
                terms of CPU operations. If you don't need to know the exact
                length (e.g. for just comparing lengths) use squaredLength()
                instead.
        */
        inline float length () const
        {
            return sqrt( x * x + y * y + z * z );
        }

        /** Returns the square of the length(magnitude) of the vector.
            @remarks
                This  method is for efficiency - calculating the actual
                length of a vector requires a square root, which is expensive
                in terms of the operations required. This method returns the
                square of the length of the vector, i.e. the same as the
                length but before the square root is taken. Use this if you
                want to find the longest / shortest vector without incurring
                the square root.
        */
        inline float squaredLength () const
        {
            return x * x + y * y + z * z;
        }

        /** Returns the distance to another vector.
            @warning
                This operation requires a square root and is expensive in
                terms of CPU operations. If you don't need to know the exact
                distance (e.g. for just comparing distances) use squaredDistance()
                instead.
        */
        inline float distance(const Vector3& other) const
        {
            return (*this - other).length();
        }

        /** Returns the square of the distance to another vector.
            @remarks
                This method is for efficiency - calculating the actual
                distance to another vector requires a square root, which is
                expensive in terms of the operations required. This method
                returns the square of the distance to another vector, i.e.
                the same as the distance but before the square root is taken.
                Use this if you want to find the longest / shortest distance
                without incurring the square root.
        */
        inline float squaredDistance(const Vector3& other) const
        {
            return (*this - other).squaredLength();
        }

        /** Calculates the dot (scalar) product of this vector with another.
            @remarks
                The dot product can be used to calculate the angle between 2
                vectors. If both are unit vectors, the dot product is the
                cosine of the angle; otherwise the dot product must be
                divided by the product of the lengths of both vectors to get
                the cosine of the angle. This result can further be used to
                calculate the distance of a point from a plane.
            @param
                vec Vector with which to calculate the dot product (together
                with this one).
            @returns
                A float representing the dot product value.
        */
        inline float dot(const Vector3& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        /** Normalises the vector.
            @remarks
                This method normalises the vector such that it's
                length / magnitude is 1. The result is called a unit vector.
            @note
                This function will not crash for zero-sized vectors, but there
                will be no changes made to their components.
            @returns The previous length of the vector.
        */
        inline void normalise()
        {
            float length = sqrt( x * x + y * y + z * z );

            // Will also work for zero-sized vectors, but will change nothing
            if ( length > 1e-08 )
            {
                float inv = 1.0f / length;
                x *= inv;
                y *= inv;
                z *= inv;
            }
        }

        /** Calculates the cross-product of 2 vectors, i.e. the vector that
            lies perpendicular to them both.
            @remarks
                The cross-product is normally used to calculate the normal
                vector of a plane, by calculating the cross-product of 2
                non-equivalent vectors which lie on the plane (e.g. 2 edges
                of a triangle).
            @param
                vec Vector which, together with this one, will be used to
                calculate the cross-product.
            @returns
                A vector which is the result of the cross-product. This
                vector will <b>NOT</b> be normalised, to maximise efficiency
                - call Vector3::normalise on the result if you wish this to
                be done. As for which side the resultant vector will be on, the
                returned vector will be on the side from which the arc from 'this'
                to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
                = UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
				This is because OGRE uses a right-handed coordinate system.
            @par
                For a clearer explanation, look a the left and the bottom edges
                of your monitor's screen. Assume that the first vector is the
                left edge and the second vector is the bottom edge, both of
                them starting from the lower-left corner of the screen. The
                resulting vector is going to be perpendicular to both of them
                and will go <i>inside</i> the screen, towards the cathode tube
                (assuming you're using a CRT monitor, of course).
        */
        inline Vector3 cross( const Vector3& other ) const
        {
            return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

		/** Gets the angle between 2 vectors.
		@remarks
			Vectors do not have to be unit-length but must represent directions.
		*/
		inline float angleBetween(const Vector3& other)
		{
			float lenProduct = length() * other.length();

			// Divide by zero check
			if(lenProduct < 1e-6f)
				lenProduct = 1e-6f;

			float f = dot(other) / lenProduct;

			return acos(f);

		}

        /** As normalise, except that this vector is unaffected and the
            normalised vector is returned as a copy. */
        inline Vector3 normalised(void) const
        {
            Vector3 ret = *this;
            ret.normalise();
            return ret;
        }

        /** Calculates a reflection vector to the plane with the given normal .
        @remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
        */
        inline Vector3 reflect(const Vector3& normal) const
        {
            return Vector3( *this - ( 2 * this->dot(normal) * normal ) );
        }

		static Vector3 lerp(Vector3 first, Vector3 second, float t){ 
			return t*(second-first)+first; 
		}

        /** Function for writing to a stream.
        */
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Vector3& v )
        {
            o << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
            return o;
        }
    };

}

#endif
