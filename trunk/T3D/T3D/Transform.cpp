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

namespace T3D
{
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


	Transform::~Transform(void)
	{
		for(int i = 0; i < children.size(); ++i)
		{
			if(NULL != children[i])
			{
				delete children[i];
			}
		}
		parent = NULL;
		children.clear();
		delete gameObject;
	}

	
	Matrix4x4 Transform::getLocalMatrix()
	{
		if (needLocalUpdate){
			calcLocalMatrix();
		}
		return localMatrix;
	}

	Matrix4x4 Transform::getWorldMatrix()
	{
		if (needWorldUpdate){
			update(false);
		}
		return worldMatrix;
	}

	void Transform::update(bool updateChildren)
	{	
		if (needLocalUpdate){
			calcLocalMatrix();
		}

		if(NULL != parent)
		{
			if (parent->needWorldUpdate){
				parent->update(false);
			}
			worldMatrix = parent->worldMatrix*localMatrix;
		} else {
			worldMatrix = localMatrix;
		}

		needWorldUpdate = false;

		if(updateChildren && !children.empty())
		{
			for(int i = 0; i < children.size(); ++i)
			{
				if(NULL != children[i])
				{
					children[i]->update(true);
				}
			}
		}
	} 

	void Transform::calcLocalMatrix(){
		Matrix4x4 scaleRotate = Matrix4x4::IDENTITY;
		scaleRotate = (scaleMatrix*rotationMatrix);
		localMatrix = translationMatrix*scaleRotate;
		
		needLocalUpdate = false;
	}

	void Transform::setNeedWorldUpdate(){
		if (!needWorldUpdate)
		{
			needWorldUpdate = true;
			if(!children.empty())
			{
				for(int i = 0; i < children.size(); ++i)
				{
					if(NULL != children[i])
					{
						children[i]->setNeedWorldUpdate();
					}
				}
			}
		}
	}


	void Transform::setLocalPosition(const Vector3& pos){
		translationMatrix.setTrans(pos);
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}		
	void Transform::setWorldPosition(const Vector3& pos){
		if (needWorldUpdate){
			update(false);
		}
		if (parent)
			setLocalPosition(pos - parent->getWorldPosition());
	}
	void Transform::setLocalRotation(const Vector3& rot){
		rotationMatrix.fromEulerAngles(rot.y,rot.x,rot.z);
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}
	void Transform::setLocalRotation(Quaternion& q){
		rotationMatrix = (Matrix3x3)q;
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}
	void Transform::setLocalScale(const Vector3& scl){
		scaleMatrix[0][0] = scl.x;
		scaleMatrix[1][1] = scl.y;
		scaleMatrix[2][2] = scl.z;
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}
		
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

	void Transform::roll(const float angle)
    {
        rotate(Vector3(0,0,1), angle);
    }
    //-----------------------------------------------------------------------
    void Transform::pitch(const float angle)
    {
        rotate(Vector3(1,0,0), angle);
    }
    //-----------------------------------------------------------------------
    void Transform::yaw(const float angle)
    {
        rotate(Vector3(0,1,0), angle);

    }
    //-----------------------------------------------------------------------
    void Transform::rotate(const Vector3& axis, const float angle)
    {
        Quaternion q = Quaternion::fromAngleAxis(angle,axis);
        rotate(q);
    }

	//-----------------------------------------------------------------------
    void Transform::rotate(const Vector3& eulers)
    {
        Quaternion q = Quaternion(eulers);
        rotate(q);
    }

    //-----------------------------------------------------------------------
    void Transform::rotate(Quaternion& q)
    {
        rotationMatrix = rotationMatrix * (Matrix3x3)q;

		needLocalUpdate = true;
		setNeedWorldUpdate();
    }

	// Make -ve z axis point at other
	void Transform::lookAt(Vector3 target, Vector3 up){
		Vector3 vectorTo = target - getWorldPosition();

		if (vectorTo.squaredLength()>0){
			// first build rotation matrix
			Vector3 zaxis = -vectorTo.normalised();
			Vector3 xaxis = zaxis.cross(up).normalised();
			Vector3 yaxis = zaxis.cross(xaxis);
			Matrix3x3 rot;
			rotationMatrix.FromAxes(xaxis,yaxis,zaxis);
		}
		needLocalUpdate = true;
		setNeedWorldUpdate();
	}

	Vector3 Transform::transformPoint(Vector3 &p){
		return getWorldMatrix()*p;
	}

	Transform* Transform::getParent(void) const
	{
		return parent;
	}

	void Transform::setParent(Transform* p)
	{
		if (parent != p)
		{
			if(NULL != parent)
			{
				parent->removeChild(this);
				parent = NULL;
			}
			if(NULL != p)
			{
				p->addChild(this);
			}
			parent = p;
			setNeedWorldUpdate();
		}
	}

	void Transform::addChild(Transform* c)
	{
		children.push_back(c);
	}

	void Transform::removeChild(Transform* c)
	{
		if(NULL != c && !children.empty())
		{
			for(int i = 0; i < children.size(); ++i)
			{
				if(children[i] == c)
				{
					children.erase(children.begin() + i);
					break; // break the for loop
				}
			}
		}
	}

	std::string Transform::getName(void) const
	{
		return name;
	}

	Transform* Transform::getChildByName(std::string n)
	{
		if(!children.empty())
		{
			for(int i = 0; i < children.size(); ++i)
			{
				if(0 == n.compare(children[i]->name))
				{
					return children[i];
				}
			}
		}
		return NULL;
	}

	Transform* Transform::getAncestorByName(std::string n)
	{
		std::queue<Transform*> q;
		Transform* current = this;

		while (current!=NULL && n.compare(current->name) != 0){
			std::cout << "processing " << current->name << "\n";
			if(!current->children.empty())
			{
				for(int i = 0; i < current->children.size(); ++i)
				{
					q.push(current->children[i]);
				}
			}
			if (q.empty()){
				current = NULL;
			} else {
				current = q.front();
				q.pop();
			}
		}
		return current;
	}
}


