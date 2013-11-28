// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// transform.h
//
// The base class for the scene graph
// Adapted from http://scriptionary.com/2009/02/17/simple-scene-graph-in-c/


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <string>
#include <iostream>
#include "Matrix4x4.h"
#include "Component.h"
#include "Quaternion.h"

namespace T3D
{
	class Transform: public Component
	{
	public:
		Transform(Transform* parent = NULL, std::string name = "noname");
		~Transform(void);
 
		virtual void update(bool updateChildren = true);
 
		Transform* getParent(void) const;
		void setParent(Transform* p);
 
	private:
		void addChild(Transform* c);
		void removeChild(Transform* c);
 
	public:
		std::string getName(void) const;
 
		Transform* getChildByName(std::string n);
		Transform* getAncestorByName(std::string n);

		void setLocalPosition(const Vector3& pos);
		void setWorldPosition(const Vector3& pos);
		void setLocalRotation(const Vector3& rot);
		void setLocalRotation(Quaternion& q);
		void setLocalScale(const Vector3& scl);

		void move(const Vector3& delta);void Transform::roll(const float angle);
		void pitch(const float angle);
		void yaw(const float angle);
		void rotate(const Vector3& axis, const float angle);
		void rotate(Quaternion& q);
		void rotate(const Vector3& eulers);

		void lookAt(Vector3 target, Vector3 up = Vector3(0,1,0));

		Matrix4x4 getLocalMatrix();
		Matrix4x4 getWorldMatrix();
		
		const Vector3 getLocalPosition();
		const Vector3 getEulerAngles();
		const Quaternion getQuaternion();
		const Matrix3x3 getRotationMatrix(){ return rotationMatrix; }
		const Vector3 getLocalScale();
		
		const Vector3 getWorldPosition();

		Vector3 transformPoint(Vector3 &p);
		
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Transform& t )
        {
			o << "Transform(" << t.name << ")";
			
			return o;
        }

	private:
		void calcLocalMatrix();
		void setNeedWorldUpdate();

		Matrix4x4 localMatrix;
		Matrix4x4 worldMatrix;
		bool needLocalUpdate;
		bool needWorldUpdate;
		
		Matrix4x4 translationMatrix;
		Matrix3x3 rotationMatrix;
		Matrix3x3 scaleMatrix;

	public:
		Transform* parent;
		std::string name;
		std::vector<Transform*> children;
	}; 
}

#endif

