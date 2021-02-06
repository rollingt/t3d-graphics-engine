// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// vector4.h
//
// 3d homogeneous vector class
// Adapted from Ogre3D
#pragma once

#include <algorithm>
#include <iostream>
#include <assert.h>
#include <math.h>

#include "Vector3.h"

namespace T3D
{
	//! \brief 4-component Vector, with homogeneous w.
	class Vector4
    {
    public:
        float x, y, z, w;

    public:
        #pragma warning(suppress: 26495) /* uninitialised member warning */
        inline Vector4()
        {
        }

        inline Vector4( const float x, const float y, const float z, const float w )
            : x( x ), y( y ), z( z ), w( w)
        {
        }

        inline explicit Vector4( const float arr[4] )
            : x( arr[0] ),
              y( arr[1] ),
              z( arr[2] ),
              w( arr[3] )
        {
        }

        inline explicit Vector4( const int arr[4] )
        {
            x = (float)arr[0];
            y = (float)arr[1];
            z = (float)arr[2];
            w = (float)arr[3];
        }

        inline explicit Vector4( float* const arr )
            : x( arr[0] ), y( arr[1] ), z( arr[2] ), w( arr[3] )
        {
        }

		/** Exchange the contents of this vector with another. 
		*/
		inline void swap(Vector4& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}
	
		inline float operator [] ( const int i ) const
        {
            assert( i < 4 );

            return *(&x+i);
        }

		inline float& operator [] ( const int i )
        {
            assert( i < 4 );

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
        inline Vector4& operator = ( const Vector4& other )
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;

            return *this;
        }

		inline Vector4& operator = ( const float s)
		{
			x = s;
			y = s;
			z = s;
			w = s;
			return *this;
		}

        inline bool operator == ( const Vector4& other ) const
        {
            return ( x == other.x &&
                y == other.y &&
                z == other.z &&
                w == other.w );
        }

        inline bool operator != ( const Vector4& other ) const
        {
            return ( x != other.x ||
                y != other.y ||
                z != other.z ||
                w != other.w );
        }

        inline Vector4& operator = (const Vector3& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = 1.0f;
            return *this;
        }

        // arithmetic operations
        inline Vector4 operator + ( const Vector4& other ) const
        {
            return Vector4(
                x + other.x,
                y + other.y,
                z + other.z,
                w + other.w);
        }

        inline Vector4 operator - ( const Vector4& other ) const
        {
            return Vector4(
                x - other.x,
                y - other.y,
                z - other.z,
                w - other.w);
        }

        inline Vector4 operator * ( const float s ) const
        {
            return Vector4(
                x * s,
                y * s,
                z * s,
                w * s);
        }

        inline Vector4 operator / ( const float s ) const
        {
            assert( s != 0.0 );

            float inv = 1.0f / s;

            return Vector4(
                x * inv,
                y * inv,
                z * inv,
                w * inv);
        }  

        inline const Vector4& operator + () const
        {
            return *this;
        }

        inline Vector4 operator - () const
        {
            return Vector4(-x, -y, -z, -w);
        }

        inline friend Vector4 operator * ( const float s, const Vector4& v )
        {
            return Vector4(
                s * v.x,
                s * v.y,
                s * v.z,
                s * v.w);
        }

        inline friend Vector4 operator / ( const float s, const Vector4& v )
        {
            return Vector4(
                s / v.x,
                s / v.y,
                s / v.z,
                s / v.w);
        }

        // arithmetic updates
        inline Vector4& operator += ( const Vector4& other )
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;

            return *this;
        }

        inline Vector4& operator -= ( const Vector4& other )
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;

            return *this;
        }

        inline Vector4& operator *= ( const float s )
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }

        inline Vector4& operator /= ( const float s )
        {
            assert( s != 0.0 );

            float inv = 1.0f / s;

            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;

            return *this;
        }

        /** Calculates the dot (scalar) product of this vector with another.
            @param
                vec Vector with which to calculate the dot product (together
                with this one).
            @returns
                A float representing the dot product value.
        */
        inline float dot(const Vector4& other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        /** Function for writing to a stream.
        */
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Vector4& v )
        {
            o << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
            return o;
        }
    };
}
