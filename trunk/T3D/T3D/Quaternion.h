// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Quaternion.h
//
// Quaternion class
// Adapted from http://willperone.net/Code/Quaternion.php
// For more information about Quaternions and the theory behind them can be found here:
//                http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer
//                http://www.cprogramming.com/tutorial/3d/quaternions.html
//                http://www.gamedev.net/page/resources/_/reference/programming/math-and-physics/quaternions/Quaternion-powers-r1095

#ifndef QUATERNION_H
#define QUATERNION_H
	
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Math.h"

namespace T3D {

	class Quaternion
	{
	public:
		union {
			struct {
				float    s; //!< the real component
				Vector3 v; //!< the imaginary components
			};
			struct { float elem[4]; }; //! the raw elements of the Quaternion
		};


		//! constructors
		Quaternion() {s=1; v = Vector3(0,0,0); }
		Quaternion(float real, float x, float y, float z): s(real), v(x,y,z) {}
		Quaternion(float real, const Vector3 &i): s(real), v(i) {}

		//! from 3 euler angles
		Quaternion(float theta_x, float theta_y, float theta_z)
		{
			float cos_z_2 = cosf(0.5f*theta_z);
			float cos_y_2 = cosf(0.5f*theta_y);
			float cos_x_2 = cosf(0.5f*theta_x);

			float sin_z_2 = sinf(0.5f*theta_z);
			float sin_y_2 = sinf(0.5f*theta_y);
			float sin_x_2 = sinf(0.5f*theta_x);

			// and now compute Quaternion
			s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;
		}
	
		//! from 3 euler angles 
		Quaternion(const Vector3 &angles)
		{	
			float cos_z_2 = cosf(0.5f*angles.z);
			float cos_y_2 = cosf(0.5f*angles.y);
			float cos_x_2 = cosf(0.5f*angles.x);

			float sin_z_2 = sinf(0.5f*angles.z);
			float sin_y_2 = sinf(0.5f*angles.y);
			float sin_x_2 = sinf(0.5f*angles.x);

			// and now compute Quaternion
			s   = cos_z_2*cos_y_2*cos_x_2 + sin_z_2*sin_y_2*sin_x_2;
			v.x = cos_z_2*cos_y_2*sin_x_2 - sin_z_2*sin_y_2*cos_x_2;
			v.y = cos_z_2*sin_y_2*cos_x_2 + sin_z_2*cos_y_2*sin_x_2;
			v.z = sin_z_2*cos_y_2*cos_x_2 - cos_z_2*sin_y_2*sin_x_2;		
		} 

		//! from rotation matrix
		Quaternion(const Matrix3x3 &m)
		{	
			float t = m[0][0]+m[1][1]+m[2][2];
			float r = sqrt(1+t);
			s = 0.5f*r;
			v.x = 0.5f*sqrt(1+m[0][0]-m[1][1]-m[2][2]); 
			if ((v.x>0 && m[2][1]-m[1][2]<0) || (v.x<0 && m[2][1]-m[1][2]>0)) v.x = -v.x;
			v.y = 0.5f*sqrt(1-m[0][0]+m[1][1]-m[2][2]); 
			if ((v.y>0 && m[0][2]-m[2][0]<0) || (v.y<0 && m[0][2]-m[2][0]>0)) v.y = -v.y;
			v.z = 0.5f*sqrt(1-m[0][0]-m[1][1]+m[2][2]); 
			if ((v.z>0 && m[1][0]-m[0][1]<0) || (v.z<0 && m[1][0]-m[0][1]>0)) v.z = -v.z;
		} 
		
		//! basic operations
		Quaternion &operator =(const Quaternion &q)		
		{ s= q.s; v= q.v; return *this; }

		const Quaternion operator +(const Quaternion &q) const	
		{ return Quaternion(s+q.s, v+q.v); }

		const Quaternion operator -(const Quaternion &q) const	
		{ return Quaternion(s-q.s, v-q.v); }

		const Quaternion operator *(const Quaternion &q) const	
		{	return Quaternion(s*q.s - v.dot(q.v),
					  v.y*q.v.z - v.z*q.v.y + s*q.v.x + v.x*q.s,
					  v.z*q.v.x - v.x*q.v.z + s*q.v.y + v.y*q.s,
					  v.x*q.v.y - v.y*q.v.x + s*q.v.z + v.z*q.s);
		}

		const Quaternion operator /(const Quaternion &q) const	
		{
			Quaternion p(q); 
			p.invert(); 
			return *this * p;
		}

		const Quaternion operator *(float scale) const
		{ return Quaternion(s*scale,v*scale); }

		const Quaternion operator /(float scale) const
		{ return Quaternion(s/scale,v/scale); }

		const Quaternion operator -() const
		{ return Quaternion(-s, -v); }
	
		const Quaternion &operator +=(const Quaternion &q)		
		{ v+=q.v; s+=q.s; return *this; }

		const Quaternion &operator -=(const Quaternion &q)		
		{ v-=q.v; s-=q.s; return *this; }

		const Quaternion &operator *=(const Quaternion &q)		
		{			
			float x= v.x, y= v.y, z= v.z, sn= s*q.s - v.dot(q.v);
			v.x= y*q.v.z - z*q.v.y + s*q.v.x + x*q.s;
			v.y= z*q.v.x - x*q.v.z + s*q.v.y + y*q.s;
			v.z= x*q.v.y - y*q.v.x + s*q.v.z + z*q.s;
			s= sn;
			return *this;
		}
	
		const Quaternion &operator *= (float scale)			
		{ v*=scale; s*=scale; return *this; }

		const Quaternion &operator /= (float scale)			
		{ v/=scale; s/=scale; return *this; }
	

		//! gets the length of this Quaternion
		float length() const
		{ return (float)sqrt(s*s + v.dot(v)); }

		//! gets the squared length of this Quaternion
		float squaredLength() const
		{ return (float)(s*s + v.dot(v)); }

		//! normalizes this Quaternion
		void normalise()
		{ *this/=length(); }

		//! returns the normalized version of this Quaternion
		Quaternion normalised() const
		{ return  *this/length(); }

		//! computes the conjugate of this Quaternion
		void conjugate()
		{ v=-v; }

		//! inverts this Quaternion
		void invert()
		{ conjugate(); *this/=squaredLength(); }
	
		//! returns the logarithm of a Quaternion = v*a where q = [cos(a),v*sin(a)]
		Quaternion log() const
		{
			float a = (float)acos(s);
			float sina = (float)sin(a);
			Quaternion ret;

			ret.s = 0.f;
			if (sina > 0.f)
			{
				ret.v.x = a*v.x/sina;
				ret.v.y = a*v.y/sina;
				ret.v.z = a*v.z/sina;
			} else {
				ret.v.x= ret.v.y= ret.v.z= 0.f;
			}
			return ret;
		}

		//! returns e^Quaternion = exp(v*a) = [cos(a),vsin(a)]
		Quaternion exp() const
		{
			float a = (float)v.length();
			float sina = (float)sin(a);
			float cosa = (float)cos(a);
			Quaternion ret;

			ret.s = cosa;
			if (a > 0.f)
			{
				ret.v.x = sina * v.x / a;
				ret.v.y = sina * v.y / a;
				ret.v.z = sina * v.z / a;
			} else {
				ret.v.x = ret.v.y = ret.v.z = 0.f;
			}
			return ret;
		}

		//! casting to a 4x4 isomorphic matrix for right multiplication with vector
		operator Matrix4x4() const
		{			
			return Matrix4x4(s,  -v.x, -v.y,-v.z,
					v.x,  s,  -v.z, v.y,
					v.y, v.z,    s,-v.x,
					v.z,-v.y,  v.x,   s);
		}
	
		//! casting to 3x3 rotation matrix
		operator Matrix3x3() 
		{
			if (fabs(squaredLength()-1.0f)>0.0001f){
				normalise();
			}
			return Matrix3x3(1-2*(v.y*v.y+v.z*v.z), 2*(v.x*v.y-s*v.z),   2*(v.x*v.z+s*v.y),   
					2*(v.x*v.y+s*v.z),   1-2*(v.x*v.x+v.z*v.z), 2*(v.y*v.z-s*v.x),   
					2*(v.x*v.z-s*v.y),   2*(v.y*v.z+s*v.x),   1-2*(v.x*v.x+v.y*v.y));
		}

		//! computes the dot product of 2 quaternions
		static inline float dot(const Quaternion &q1, const Quaternion &q2) 
		{ return q1.v.dot(q2.v) + q1.s*q2.s; }

		//! linear Quaternion interpolation
		static Quaternion lerp(const Quaternion &q1, const Quaternion &q2, float t) 
		{ return (q1*(1-t) + q2*t).normalised(); }

		//! spherical linear interpolation
		static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) 
		{
			Quaternion q3;
			float dot = Quaternion::dot(q1, q2);

			/*	dot = cos(theta)
				if (dot < 0), q1 and q2 are more than 90 degrees apart,
				so we can invert one to reduce spinning	*/
			if (dot < 0)
			{
				dot = -dot;
				q3 = -q2;
			} else q3 = q2;
		
			if (dot < 0.95f)
			{
				float angle = acosf(dot);
				return (q1*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
			} else // if the angle is small, use linear interpolation								
				return lerp(q1,q3,t);		
		}

		//! This version of slerp, used by squad, does not check for theta > 90.
		static Quaternion slerpNoInvert(const Quaternion &q1, const Quaternion &q2, float t) 
		{
			float dot = Quaternion::dot(q1, q2);

			if (dot > -0.95f && dot < 0.95f)
			{
				float angle = acosf(dot);			
				return (q1*sinf(angle*(1-t)) + q2*sinf(angle*t))/sinf(angle);
			} else  // if the angle is small, use linear interpolation								
				return lerp(q1,q2,t);			
		}

		//! spherical cubic interpolation
		static Quaternion squad(const Quaternion &q1,const Quaternion &q2,const Quaternion &a,const Quaternion &b,float t)
		{
			Quaternion c= slerpNoInvert(q1,q2,t),
					   d= slerpNoInvert(a,b,t);		
			return slerpNoInvert(c,d,2*t*(1-t));
		}

		//! Shoemake-Bezier interpolation using De Castlejau algorithm
		static Quaternion bezier(const Quaternion &q1,const Quaternion &q2,const Quaternion &a,const Quaternion &b,float t)
		{
			// level 1
			Quaternion q11= slerpNoInvert(q1,a,t),
					q12= slerpNoInvert(a,b,t),
					q13= slerpNoInvert(b,q2,t);		
			// level 2 and 3
			return slerpNoInvert(slerpNoInvert(q11,q12,t), slerpNoInvert(q12,q13,t), t);
		}

		//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
		static Quaternion spline(const Quaternion &qnm1,const Quaternion &qn,const Quaternion &qnp1)
		{
			Quaternion qni(qn.s, -qn.v);	
			return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
		}

		//! converts from a normalized axis - angle pair rotation to a Quaternion
		static inline Quaternion fromAngleAxis(float angle, const Vector3 &axis)
		{ return Quaternion(cosf(angle/2), axis*sinf(angle/2)); }

		//! returns the axis and angle of this unit Quaternion
		void toAngleAxis(float &angle, Vector3 &axis) 
		{
			if (s>1) normalise();
			angle = 2.0f*acosf(s);
			float k = sqrt(1-s*s);

			if (k<0.0001){
				axis.x = 0; axis.y = 0; axis.z = 1;
			} else {
				axis.x = v.x/k;
				axis.y = v.y/k;
				axis.z = v.z/k;
			}
		}

		//! rotates v by this Quaternion (Quaternion must be unit)
		Vector3 rotate(const Vector3 &v)
		{   
			Quaternion V(0, v);
			Quaternion conjugate(*this);
			conjugate.conjugate();
			return (*this * V * conjugate).v;
		}

		//! returns the euler angles from a rotation Quaternion
		Vector3 eulerAngles() const
		{
			float sqw = s*s;    
			float sqx = v.x*v.x;    
			float sqy = v.y*v.y;    
			float sqz = v.z*v.z;    
			
			float unit = sqx + sqy + sqz + sqw;
			float test = v.x * v.y + v.z * s;

			Vector3 euler;

			if (test > 0.4999f * unit) // Singularity at north pole                       
			{				
				euler.y = 2.f * (float)atan2f(v.x, s);  // Yaw
				euler.z = Math::PI * 0.5f;              // Roll
				euler.x = 0.f;                          // Pitch
				return euler;
			}
			else if (test < -0.4999f * unit) // Singularity at south pole                     
			{
				euler.y = -2.f * (float)atan2f(v.x, s); // Yaw
				euler.z = -Math::PI * 0.5f;             // Roll
				euler.x = 0.f;                          // Pitch
				return euler;
			}
			else
			{
				euler.y = (float)atan2f(2.f * v.y * s - 2.f * v.x * v.z, sqx - sqy - sqz + sqw);       // Yaw
				euler.z = (float)asinf(2.f * test / unit);                                             // Roll
				euler.x = (float)atan2f(2.f * v.x * s - 2.f * v.y * v.z, -sqx + sqy - sqz + sqw);      // Pitch
			} 
			return euler;
		}

		/** Function for writing to a stream.
        */
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Quaternion& q )
        {
            o << "Quat(" << q.s << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z << ")";
            return o;
        }
	};
}

#endif 

