#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "Component.h"
#include "Bullet/include/LinearMath/btMotionState.h"
#include "Bullet/include/LinearMath/btTransform.h"

class btRigidBody;

class ComponentRigidbody : public Component, public btMotionState
{
public:
	enum MotionType
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

public:
	ComponentRigidbody(GameObject * parent);
	~ComponentRigidbody();

	float getMass()
	{

		return mass;
	}

	btRigidBody* rigid_body = nullptr;

private:

	float mass;
};

#endif // !COMPONENTRIGIDBODY_H