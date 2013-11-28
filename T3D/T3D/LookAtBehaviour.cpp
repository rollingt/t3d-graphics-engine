#include "LookAtBehaviour.h"
#include "GameObject.h"

namespace T3D
{
	
	LookAtBehaviour::~LookAtBehaviour(void)
	{
	}

	void LookAtBehaviour::update(float dt){
		gameObject->getTransform()->lookAt(target->getWorldPosition());
	}

}
