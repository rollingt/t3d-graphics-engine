// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// transform.cpp
//
// The base class for the scene graph
// Adapted from http://scriptionary.com/2009/02/17/simple-scene-graph-in-c/

#include <queue>

#include "Transform.h"
#include "GameObject.h"
#include "Logger.h"

namespace T3D
{
	/*
	 * This sets up local and world matrices for the transform, and resets clears update flags.
	 *
	 * \param p	Parent transform
	 * \param n	Name of transform
	 */
	Transform::Transform(Transform* p, std::string n)
	{
		name = n;

		parent = NULL;
		setParent(p);

		localMatrix = Matrix4x4::IDENTITY;

		if (p!=NULL){
			worldMatrix = p->worldMatrix;
		} else { 
			worldMatrix = Matrix4x4::IDENTITY;
		}

		translationMatrix = Matrix4x4::IDENTITY;
		scaleMatrix = Matrix3x3::IDENTITY;
		rotationMatrix = Matrix3x3::IDENTITY;
		needLocalUpdate = false;
		needWorldUpdate = false;
	} 


	/*
	 * \note T3D manages GameObject memory by destroying children of a scenegraph, *then* destroying the GameObject and its components. 
	 */
	Transform::~Transform(void)
	{
		// NOTE:
		// This leaks memory, as removeChild() invalidates the size of the calling node's subtree.
		// Given a std::vector of nodes, V, when `V.erase` is called on any index n, V will shuffle elements from [n + 1...V.size()].
		// This shuffle is to ensure elements are densely contiguous in memory. It means that as the indices increase, half the scene graph
		// is not deleted. It just happens to not segfalt because the condition `V.size()` is not inlined. 
		//
		// A solution to this without a large refactoring of the component system would be to use std::shared_ptr or handles.
		for (uint32_t child = 0; child < children.size(); child++) {
			if (children[child]) delete children[child];
		}

		if (parent) {
			parent->removeChild(this);  /* invalidates iterator of parent! */
			parent = NULL;
		}
		children.clear();

		delete gameObject;
	}

	/*
	 * \param updateChildren Recursively update or not
	 */
	void Transform::update(bool updateChildren)
	{	
		if (needLocalUpdate) calcLocalMatrix();

		/* If this transform isn't the root, concatenate the parents matrix (operator '*' here)
		   with ours after checking if parent needs an update.  Otherwise, this transform is
		   the root and is synonymous with world space. */
		if (parent) 
		{
			if (parent->needWorldUpdate) parent->update(false);
			worldMatrix = parent->worldMatrix*localMatrix;
		} 
		else 
		{
			worldMatrix = localMatrix;
		}

		needWorldUpdate = false;

		if(updateChildren)
		{
			for (auto child: children)
			{
				child->update(true);
			}
		}
	} 

	void Transform::calcLocalMatrix(){
		Matrix4x4 scaleRotate = Matrix4x4::IDENTITY;
		scaleRotate = (rotationMatrix*scaleMatrix);
		localMatrix = translationMatrix*scaleRotate;
		
		needLocalUpdate = false;
	}

	void Transform::setNeedWorldUpdate(){
		if (!needWorldUpdate)
		{
			needWorldUpdate = true;
			for (auto child: children)
			{
				if (child) child->setNeedWorldUpdate();
			}
		}
	}


	/*
	 * \param pos new local position
	 */
	void Transform::setLocalPosition(const Vector3& pos){
		translationMatrix.setTrans(pos);
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}		

	/*
	 * \param pos new world position
	 */
	void Transform::setWorldPosition(const Vector3& pos){
		if (needWorldUpdate){
			update(false);
		}
		if (parent)
			setLocalPosition(pos - parent->getWorldPosition());
	}

	/*
	 * \param rot new local rotation, as euler angles
	 */
	void Transform::setLocalRotation(const Vector3& rot){
		rotationMatrix.fromEulerAngles(rot.y,rot.x,rot.z);
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}

	/*
	 * \param q new local rotation, as quaternion
	 */
	void Transform::setLocalRotation(Quaternion& q){
		rotationMatrix = (Matrix3x3)q;
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}

	/*
	 * \param scl new scale
	 * \note This may have strange behaviour for non-uniform scaling
	 */
	void Transform::setLocalScale(const Vector3& scl){
		scaleMatrix[0][0] = scl.x;
		scaleMatrix[1][1] = scl.y;
		scaleMatrix[2][2] = scl.z;
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}
		
	/*
	 * \param delta Movement terms
	 */
	const Vector3 Transform::getLocalPosition(){
		return translationMatrix.getTrans();
	}
		
	const Vector3 Transform::getWorldPosition(){
		if (needWorldUpdate){
			update(false);
		}
		return worldMatrix.getTrans();
	}

	const Vector3 Transform::getEulerAngles(){
		Vector3 v;
		rotationMatrix.toEulerAngles(v.y,v.x,v.z);
		return v;
	}
	const Quaternion Transform::getQuaternion(){
		return Quaternion(rotationMatrix);
	}
	const Vector3 Transform::getLocalScale(){
		return Vector3(scaleMatrix[0][0],scaleMatrix[1][1],scaleMatrix[2][2]);
	}

	void Transform::move(const Vector3& delta){
		translationMatrix[0][3] += delta.x;
		translationMatrix[1][3] += delta.y;
		translationMatrix[2][3] += delta.z;

		needLocalUpdate = true;
		setNeedWorldUpdate();
	}

	/*
	 * \param angle rotation angle
	 */
	void Transform::roll(const float angle)
    {
        rotate(Vector3(0,0,1), angle);
    }

	/*
	 * \param angle rotation angle
	 */
    void Transform::pitch(const float angle)
    {
        rotate(Vector3(1,0,0), angle);
    }

	/*
	 * \param angle rotation angle
	 */
    void Transform::yaw(const float angle)
    {
        rotate(Vector3(0,1,0), angle);
    }

	/*
	 * \param axis Masked axis to move about
	 * \param angle rotation angle
	 */
    void Transform::rotate(const Vector3& axis, const float angle)
    {
        Quaternion q = Quaternion::fromAngleAxis(angle,axis);
        rotate(q);
    }

	/*
	 * \param eulers rotation euler angles
	 */
    void Transform::rotate(const Vector3& eulers)
    {
        Quaternion q = Quaternion(eulers);
        rotate(q);
    }

	/*
	 * \param q rotation quaternion
	 */
    void Transform::rotate(Quaternion& q)
    {
        rotationMatrix = rotationMatrix * (Matrix3x3)q;

		needLocalUpdate = true;
		setNeedWorldUpdate();
    }

	/*
	 * This works by making -ve z axis point at other
	 *
	 * \param target transform to look at
	 * \param up upwards direction relative to transform
	 */
	void Transform::lookAt(Vector3 target, Vector3 up){
		Vector3 vectorTo = target - getWorldPosition();

		if (vectorTo.squaredLength()>0){
			// first build rotation matrix
			Vector3 zaxis = -vectorTo.normalised();
			Vector3 xaxis = -zaxis.cross(up).normalised();
			Vector3 yaxis = zaxis.cross(xaxis);
			rotationMatrix.FromAxes(xaxis,yaxis,zaxis);
		}
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}

	Matrix4x4 Transform::getLocalMatrix()
	{
		if (needLocalUpdate) calcLocalMatrix();
		return localMatrix;
	}

	Matrix4x4 Transform::getWorldMatrix()
	{
		if (needWorldUpdate) update(false);
		return worldMatrix;
	}

	Vector3 Transform::transformPoint(Vector3 &p){
		return getWorldMatrix()*p;
	}

	Transform* Transform::getParent(void) const
	{
		return parent;
	}

	/*
	 * \param p New parent
	 */
	void Transform::setParent(Transform* p)
	{
		if (parent != p)
		{
			if(parent)
			{
				parent->removeChild(this);
				parent = NULL;
			}
			if(p)
			{
				p->addChild(this);
			}
			parent = p;
			setNeedWorldUpdate();
		}
	}

	std::string Transform::getName(void) const
	{
		return name;
	}

	/*
	 * \param n Name of child.
	 * \return The child or `NULL`
	 */
	Transform* Transform::getChildByName(std::string n)
	{
		for(auto child: children)
		{
			if(0 == n.compare(child->name))
			{
				return child;
			}
		}

		logger::Log(priority::Warning,
					output_stream::File,
					category::Game,
					"Warning: Searched for nonexistent child by name in scenegraph.\n"
					"\tRoot of scenegraph name: %s\n"
					"\tChild name             : %s\n"
					,
					this->name.c_str(),
					n.c_str());

		return NULL;
	}

	/*
	 * \param n Name of ancestor.
	 * \return The ancestor or `NULL`
	 */
	Transform* Transform::getAncestorByName(std::string n)
	{
		logger::Log(priority::Info,
					output_stream::File,
					category::Game,
					"Searching scenegraph from child %s for ancestor node %s...."
					,
					this->name.c_str(),
					n.c_str());
					
		std::queue<Transform*> q;
		Transform* current = this;

		while (current && n.compare(current->name) != 0) {
			logger::Log(priority::Info,
						output_stream::File,
						category::Game,
						"processing %s...." , current->name.c_str());

			for (auto child: current->children) {
				q.push(child);
			}

			if (q.empty()) {
				current = NULL;
			} else {
				current = q.front();
				q.pop();
			}
		}

		return current;
	}

	/*
	 * \param c child to add
	 */
	void Transform::addChild(Transform* c)
	{
		children.push_back(c);
	}


	/*
	 * \param c child to remove
	 * \note Does nothing if `c` is `NULL` or isn't a child of the Transform
	 */
	void Transform::removeChild(Transform* c)
	{
		if(!c) return;

		for(unsigned int i = 0; i < children.size(); ++i)
		{
			if(children[i] == c)
			{
				children.erase(children.begin() + i);
				break; // break the for loop
			}
		}
	}
}


