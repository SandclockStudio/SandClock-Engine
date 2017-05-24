#include "ComponentRigidbody.h"
#include "GameObject.h"
#include "ComponentTransform.h"

ComponentRigidbody::ComponentRigidbody(bool start_enabled, btRigidBody* rb) : rigid(rb)
{
	
}

ComponentRigidbody::~ComponentRigidbody()
{
}

bool ComponentRigidbody::Update(Frustum f)
{

	rigid->setGravity(btVector3(0, 0, 0));
	btTransform transform;
	rigid_body->getWorldTransform(transform);
	btVector3 newPosition = transform.getOrigin();
	btQuaternion rotation = transform.getRotation();
	aiVector3D position = myGo->getPosition();
	aiVector3D aux = aiVector3D( newPosition.getX(), newPosition.getY(), newPosition.getZ());
	myGo->setPosition(aux);
	Quat auxQ = Quat(rotation.getX(),  rotation.getY(), rotation.getZ(), rotation.getW());
	myGo->setRotation(auxQ);
	return true;
}
