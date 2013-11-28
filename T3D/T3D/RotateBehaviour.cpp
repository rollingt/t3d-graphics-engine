#include "rotatebehaviour.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"

namespace T3D
{

	RotateBehaviour::RotateBehaviour(Vector3 r)
	{
		rotation = r;
	}


	RotateBehaviour::~RotateBehaviour(void)
	{
	}

	
	void RotateBehaviour::update(float dt){
		gameObject->getTransform()->rotate(rotation*dt);
	}

}