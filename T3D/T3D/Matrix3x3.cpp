// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// matrix3x3.cpp
//
// 3x3 matrix class
// Adapted from Ogre3D

#include "Matrix3x3.h"
#include "Math.h"

namespace T3D
{
	const Matrix3x3 Matrix3x3::ZERO(0,0,0,0,0,0,0,0,0);
    const Matrix3x3 Matrix3x3::IDENTITY(1,0,0,0,1,0,0,0,1);

    //-----------------------------------------------------------------------
    Vector3 Matrix3x3::GetColumn (int c) const
    {
        assert( 0 <= c && c < 3 );
        return Vector3(m[0][c],m[1][c],
            m[2][c]);
    }
    //-----------------------------------------------------------------------
    void Matrix3x3::SetColumn(int c, const Vector3& vec)
    {
        assert( 0 <= c && c < 3 );
        m[0][c] = vec.x;
        m[1][c] = vec.y;
        m[2][c] = vec.z;

    }
	//-----------------------------------------------------------------------
    void Matrix3x3::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
    {
        SetColumn(0,xAxis);
        SetColumn(1,yAxis);
        SetColumn(2,zAxis);

    }

    //-----------------------------------------------------------------------
    bool Matrix3x3::operator== (const Matrix3x3& other) const
    {
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if ( m[r][c] != other.m[r][c] )
                    return false;
            }
        }

        return true;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::operator+ (const Matrix3x3& other) const
    {
        Matrix3x3 sum;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                sum.m[r][c] = m[r][c] +
                    other.m[r][c];
            }
        }
        return sum;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::operator- (const Matrix3x3& other) const
    {
        Matrix3x3 diff;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                diff.m[r][c] = m[r][c] -
                    other.m[r][c];
            }
        }
        return diff;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::operator* (const Matrix3x3& other) const
    {
        Matrix3x3 prod;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                prod.m[r][c] =
                    m[r][0]*other.m[0][c] +
                    m[r][1]*other.m[1][c] +
                    m[r][2]*other.m[2][c];
            }
        }
        return prod;
    }
    //-----------------------------------------------------------------------
    Vector3 Matrix3x3::operator* (const Vector3& p) const
    {
        Vector3 prod;
        for (int r = 0; r < 3; r++)
        {
            prod[r] =
                m[r][0]*p[0] +
                m[r][1]*p[1] +
                m[r][2]*p[2];
        }
        return prod;
    }
    //-----------------------------------------------------------------------
    Vector3 operator* (const Vector3& p, const Matrix3x3& m)
    {
        Vector3 prod;
        for (int r = 0; r < 3; r++)
        {
            prod[r] =
                p[0]*m.m[0][r] +
                p[1]*m.m[1][r] +
                p[2]*m.m[2][r];
        }
        return prod;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::operator- () const
    {
        Matrix3x3 neg;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
                neg[r][c] = -m[r][c];
        }
        return neg;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::operator* (float s) const
    {
        Matrix3x3 prod;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
                prod[r][c] = s*m[r][c];
        }
        return prod;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 operator* (float s, const Matrix3x3& m)
    {
        Matrix3x3 prod;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
                prod[r][c] = s*m.m[r][c];
        }
        return prod;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::transpose () const
    {
        Matrix3x3 trans;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
                trans[r][c] = m[c][r];
        }
        return trans;
    }
    //-----------------------------------------------------------------------
    Matrix3x3 Matrix3x3::inverse (float tolerance) const
    {
        Matrix3x3 inv = Matrix3x3::ZERO;
        inv[0][0] = m[1][1]*m[2][2] -
            m[1][2]*m[2][1];
        inv[0][1] = m[0][2]*m[2][1] -
            m[0][1]*m[2][2];
        inv[0][2] = m[0][1]*m[1][2] -
            m[0][2]*m[1][1];
        inv[1][0] = m[1][2]*m[2][0] -
            m[1][0]*m[2][2];
        inv[1][1] = m[0][0]*m[2][2] -
            m[0][2]*m[2][0];
        inv[1][2] = m[0][2]*m[1][0] -
            m[0][0]*m[1][2];
        inv[2][0] = m[1][0]*m[2][1] -
            m[1][1]*m[2][0];
        inv[2][1] = m[0][1]*m[2][0] -
            m[0][0]*m[2][1];
        inv[2][2] = m[0][0]*m[1][1] -
            m[0][1]*m[1][0];

        float det =
            m[0][0]*inv[0][0] +
            m[0][1]*inv[1][0]+
            m[0][2]*inv[2][0];

        assert(abs(det) > tolerance);

        float invDet = 1.0/det;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
                inv[r][c] *= invDet;
        }
        return inv;
    }

	
    //-----------------------------------------------------------------------
    float Matrix3x3::determinant () const
    {
        float cofactor00 = m[1][1]*m[2][2] -
            m[1][2]*m[2][1];
        float cofactor10 = m[1][2]*m[2][0] -
            m[1][0]*m[2][2];
        float cofactor20 = m[1][0]*m[2][1] -
            m[1][1]*m[2][0];

        float det =
            m[0][0]*cofactor00 +
            m[0][1]*cofactor10 +
            m[0][2]*cofactor20;

        return det;
    }

	bool Matrix3x3::toEulerAngles(float& yAngle, float& pAngle, float& rAngle) const
    {
        pAngle = asin(-m[1][2]);
        if ( pAngle < Math::HALF_PI)
        {
            if ( pAngle > -Math::HALF_PI )
            {
                yAngle = atan2(m[0][2],m[2][2]);
                rAngle = atan2(m[1][0],m[1][1]);
                return true;
            }
            else
            {
                // WARNING.  Not a unique solution.
                float fRmY = atan2(m[0][2],m[0][0]);
                rAngle = 0.0;  // any angle works
                yAngle = rAngle - fRmY;
                return false;
            }
        }
        else
        {
            // WARNING.  Not a unique solution.
            float fRpY = atan2(-m[0][1],m[0][0]);
            rAngle = 0.0;  // any angle works
            yAngle = fRpY - rAngle;
            return false;
        }
		

		/*
		// x = atan2(R(3,2), R(3,3));
		pAngle = atan2(m[2][1],m[2][2]);
		// y = atan2(-R(3,1), sqrt(R(3,2)*R(3,2) + R(3,3)*R(3,3)));
		yAngle = atan2(-m[2][0],sqrt(m[2][1]*m[2][1] + m[2][2]*m[2][2]));
		// z = atan2(R(2,1), R(1,1));
		rAngle = atan2(m[1][0],m[0][0]);
		*/
		return true;
    }

	void Matrix3x3::fromEulerAngles(const float& yAngle, const float& pAngle, const float& rAngle)
    {
        float c, s;

        c = cos(yAngle);
        s = sin(yAngle);
        Matrix3x3 yMat(c,0.0,s,0.0,1.0,0.0,-s,0.0,c);

        c = cos(pAngle);
        s = sin(pAngle);
        Matrix3x3 xMat(1.0,0.0,0.0,0.0,c,-s,0.0,s,c);

        c = cos(rAngle);
        s = sin(rAngle);
        Matrix3x3 zMat(c,-s,0.0,s,c,0.0,0.0,0.0,1.0);

        //*this = zMat*(yMat*xMat);
		*this = yMat*(xMat*zMat);
    }
}
