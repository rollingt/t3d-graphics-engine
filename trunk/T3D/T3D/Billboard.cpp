#include "Billboard.h"
#include "PlaneMesh.h"
#include "GameObject.h"
#include "T3DApplication.h"
#include "Camera.h"

namespace T3D
{
	Billboard::~Billboard(void)
	{
	}
	
	void Billboard::init(GameObject* go){
		gameObject = go;
		
		PlaneMesh *mesh = new PlaneMesh(10); 
		gameObject->setMesh(mesh);
	}
	
	void Billboard::update(float dt){	
		Vector3 target = camera->getWorldPosition();

		if (lockY){
			target.y = gameObject->getTransform()->getWorldPosition().y;
		}

		gameObject->getTransform()->lookAt(target);
		Quaternion q  = Quaternion::fromAngleAxis(-Math::HALF_PI, Vector3(1,0,0));
		gameObject->getTransform()->rotate(q);
	}

}
