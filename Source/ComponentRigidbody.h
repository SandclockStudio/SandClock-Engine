#ifndef COMPONENTRIGIDBODY_H
#define COMPONENTRIGIDBODY_H

#include "Component.h"
#include "Bullet/include/LinearMath/btMotionState.h"
#include "Bullet/include/LinearMath/btTransform.h"
#include "ModulePhysics.h"

class btRigidBody;

class ComponentRigidbody : public Component
{
public:
	enum MotionType
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

public:
	ComponentRigidbody(bool start_enabled, btRigidBody* rb);
	~ComponentRigidbody();

	bool Update(Frustum f);

	float getMass()
	{
		return mass;
	}

	void setMass(float m);

	btRigidBody* rigid;
	btMotionState* rigid_body = nullptr;

private:

	float mass;
};

#endif // !COMPONENTRIGIDBODY_H