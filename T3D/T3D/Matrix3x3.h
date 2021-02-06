// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// matrix3x3.h
//
// 3x3 matrix class
// Adapted from Ogre3D
#pragma once

#include <assert.h>
#include <string>

#include "Vector3.h"

namespace T3D
{
	//! \brief 3x3 Matrix, suitable for 2D affine transformations using homogeneous coordinates or storing 3d rotation/scale.
    class Matrix3x3
    {
    protected:
        /// The matrix entries, indexed by [row][col].
        union {
            float m[3][3];
            float _m[9];
        };
    public:
        /** Default constructor.
            @note
                It does <b>NOT</b> initialize the matrix for efficiency.
        */
        #pragma warning(suppress: 26495) /* uninitialised member warning */
		inline Matrix3x3 () {}

        inline explicit Matrix3x3 (const float arr[3][3])
		{
			memcpy(m,arr,9*sizeof(float));
		}

        inline Matrix3x3 (const Matrix3x3& other)
		{
			memcpy(m,other.m,9*sizeof(float));
		}

        Matrix3x3 (float m00, float m01, float m02,
                    float m10, float m11, float m12,
                    float m20, float m21, float m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}

		/** Exchange the contents of this matrix with another. 
		*/
		inline void swap(Matrix3x3& other)
		{
			std::swap(m[0][0], other.m[0][0]);
			std::swap(m[0][1], other.m[0][1]);
			std::swap(m[0][2], other.m[0][2]);
			std::swap(m[1][0], other.m[1][0]);
			std::swap(m[1][1], other.m[1][1]);
			std::swap(m[1][2], other.m[1][2]);
			std::swap(m[2][0], other.m[2][0]);
			std::swap(m[2][1], other.m[2][1]);
			std::swap(m[2][2], other.m[2][2]);
		}

        // member access, allows use of construct mat[r][c]
        inline float* operator[] (int iRow) const
		{
			return (float*)m[iRow];
		}

        Vector3 GetColumn (int iCol) const;

        void SetColumn(int iCol, const Vector3& vec);

        void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

        // assignment and comparison
        inline Matrix3x3& operator= (const Matrix3x3& other)
		{
			memcpy(m,other.m,9*sizeof(float));
			return *this;
		}
        bool operator== (const Matrix3x3& other) const;

        inline bool operator!= (const Matrix3x3& other) const
		{
			return !operator==(other);
		}

        // arithmetic operations
        Matrix3x3 operator+ (const Matrix3x3& other) const;
        Matrix3x3 operator- (const Matrix3x3& other) const;
        Matrix3x3 operator* (const Matrix3x3& other) const;
        Matrix3x3 operator- () const;

        // matrix * vector [3x3 * 3x1 = 3x1]
        Vector3 operator* (const Vector3& v) const;

        // vector * matrix [1x3 * 3x3 = 1x3]
        friend Vector3 operator* (const Vector3& v, const Matrix3x3& m);

        // matrix * scalar
        Matrix3x3 operator* (float s) const;

        // scalar * matrix
        friend Matrix3x3 operator* (float s, const Matrix3x3& m);

        // utilities
        Matrix3x3 transpose () const;
        Matrix3x3 inverse (float tolerance = 1e-06) const;
        float determinant () const;

		// The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
        // where yaw is rotation about the Up vector, pitch is rotation about the
        // Right axis, and roll is rotation about the Direction axis.
        
        bool toEulerAngles(float& yAngle, float& pAngle, float& rAngle) const;        
        void fromEulerAngles(const float& yAngle, const float& pAngle, const float& rAngle);

		/** Function for writing to a stream.
		*/
		inline friend std::ostream& operator <<
			( std::ostream& o, const Matrix3x3& mat )
		{
			o << "Matrix3x3(" << mat[0][0] << ", " << mat[0][1] << ", " << mat[0][2] << ", " 
                            << mat[1][0] << ", " << mat[1][1] << ", " << mat[1][2] << ", " 
                            << mat[2][0] << ", " << mat[2][1] << ", " << mat[2][2] << ")";
			return o;
		}

        static const float EPSILON;
        static const Matrix3x3 ZERO;
        static const Matrix3x3 IDENTITY;

    protected:

        // for faster access
        friend class Matrix4x4;
    };
	/** @} */
	/** @} */
}
