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
#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Component.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace T3D
{
	//! \brief Transform nodes form a hierarchical scene graph. 
	/*
	 * A Transform has a position and rotation relative to an optional parent Transform, and a container of optional children Transforms.
	 * The root of a scene and its immediate children define world space.
	 * 
	 * The implementation is similiar to Ogre3D's lazily updated hieararchical scenegraph that only updates local matrices of descendants when there has been a change to an ancestor.
	 *
	 * Many convenient functions are provided for querying, adding and updating Transforms with respect to the hierarchy.
	 *
	 */
	class Transform: public Component
	{
	public:
		//! \brief Create named Transform relative to a parent.
		Transform(Transform* parent = NULL, std::string name = "noname");

		//! \brief Destroy Transform and its children.
		~Transform(void);
 
		//! \brief Update the scenegraph, recursively by default.
		virtual void update(bool updateChildren = true);
 
		//! \brief Get parent
		Transform* getParent(void) const;

		//! \brief Set parent, updating the hierarchy recursively.
		void setParent(Transform* p);
 
		//! \brief Get name
		std::string getName(void) const;
 
		//! \brief Get child by name. Does not recurse.
		Transform* getChildByName(std::string n);

		//! \brief Get ancestor by name.
		Transform* getAncestorByName(std::string n);

		//! \brief Set local position, updating children if needed.
		void setLocalPosition(const Vector3& pos);

		//! \brief Set world position, updating children if needed.
		void setWorldPosition(const Vector3& pos);

		//! \brief Set local rotation, updating children if needed.
		void setLocalRotation(const Vector3& rot);

		//! \brief Set local rotation, updating children if needed.
		void setLocalRotation(Quaternion& q);

		//! \brief Set local scale, updating children if needed.
		void setLocalScale(const Vector3& scl);

		//! \brief Update position by moving (translate) a distance
		void move(const Vector3& delta);

		//! \brief Update rotation, by rolling by an angle
		void roll(const float angle);

		//! \brief Update rotation by pitching by an angle
		void pitch(const float angle);

		//! \brief Update rotation by yawing by an angle
		void yaw(const float angle);

		//! \brief Update rotation using an angle-axis pair
		void rotate(const Vector3& axis, const float angle);

		//! \brief Update rotation using a quaternion
		void rotate(Quaternion& q);

		//! \brief Update rotation using euler angles
		void rotate(const Vector3& eulers);

		//! \brief Update rotation by 'looking at' a target transform
		void lookAt(Vector3 target, Vector3 up = Vector3(0,1,0));

		//! \brief Get local matrix, i.e. relative to parent
		Matrix4x4 getLocalMatrix();

		//! \brief Get world matrix, i.e. relative to root of scene graph
		Matrix4x4 getWorldMatrix();

		//! \brief Get local position, i.e. relative to parent
		const Vector3 getLocalPosition();

		//! \brief Get local rotation as euler angles,
		const Vector3 getEulerAngles();

		//! \brief Get local rotation as quaternion, 
		const Quaternion getQuaternion();

		//! \brief Get rotation matrix, i.e. without transform component
		const Matrix3x3 getRotationMatrix(){ return rotationMatrix; }

		//! \brief Get local scale, i.e. relative to parent
		const Vector3 getLocalScale();
		
		//! \brief Get world postion, i.e. relative to root of scene graph
		const Vector3 getWorldPosition();

		//! \brief Move a point `P` into world space `S` relative to this transforms world space
		Vector3 transformPoint(Vector3 &p);
		
        inline friend std::ostream& operator <<
            ( std::ostream& o, const Transform& t )
        {
			o << "Transform(" << t.name << ")";
			
			return o;
        }

		//! \brief Parent of Transform. `NULL` for the root.
		Transform* parent;

		//! \brief Name of this Transform, for searching/querying/animation bones/debugging. Defaults to `noname`.
		std::string name;

		//! \brief Children of Transform. size() == 0 for a leaf Transform.
		std::vector<Transform*> children;

	private:

		//! \brief Add child.
		void addChild(Transform* c);

		//! \brief Remove child
		void removeChild(Transform* c);

		//! \brief Update local matrix and reset local dirty bit.
		void calcLocalMatrix();

		//! \brief Set world update bit to dirty.
		void setNeedWorldUpdate();

		//! \brief Matrix relative to parent.
		Matrix4x4 localMatrix;

		//! \brief Matrix relative to root of scene graph.
		Matrix4x4 worldMatrix;

		//! \brief Local update flag.
		bool needLocalUpdate;

		//! \brief World update flag.
		bool needWorldUpdate;
		
		//! \brief Translation component of local matrix.
		Matrix4x4 translationMatrix;

		//! \brief Rotation component of local matrix.
		Matrix3x3 rotationMatrix;

		//! \brief Scale component of local matrix.
		Matrix3x3 scaleMatrix;

	}; 
}
