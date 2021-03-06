#include "ComponentRigidbody.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "Application.h"


ComponentRigidbody::ComponentRigidbody(bool start_enabled, btRigidBody* rb) : rigid(rb)
{
	
}

ComponentRigidbody::~ComponentRigidbody()
{
}

bool ComponentRigidbody::Update(Frustum f)
{
	if (App->physics->IsEnabled())
	{

		App->physics->world->synchronizeMotionStates();
		btTransform transform;
		//rigid->getWorldTransform(transform);
		transform = rigid->getWorldTransform();
		btVector3 newPosition = transform.getOrigin();
		btQuaternion rotation = transform.getRotation();
		aiVector3D position = myGo->getPosition();
		aiVector3D aux = aiVector3D(newPosition.getX(), newPosition.getY(), newPosition.getZ());
		myGo->setPosition(aux);
		Quat auxQ = Quat(rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());
		//myGo->setRotation(auxQ);


	}
			
	
	return true;
}

void ComponentRigidbody::changedWorld()
{
	App->physics->world->removeRigidBody(rigid);
	rigid->activate(true);
	rigid->clearForces();
	btVector3 zeroVector(0, 0, 0);
	rigid->setLinearVelocity(zeroVector);
	rigid->setAngularVelocity(zeroVector);
	rigid->getWorldTransform().setIdentity();
	rigid->getWorldTransform().setOrigin(btVector3(myGo->getPosition().x, myGo->getPosition().y, myGo->getPosition().z));
	App->physics->world->addRigidBody(rigid);
}

void ComponentRigidbody::setMass(float m)
{
	mass = m;
	App->physics->world->removeRigidBody(rigid);
	btVector3 inertia(0, 0, 0);
	rigid->getCollisionShape()->calculateLocalInertia(mass, inertia);
	rigid->setMassProps(mass, inertia);
	App->physics->world->addRigidBody(rigid);
	
}


