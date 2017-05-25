#include "ModulePhysics.h"
#include "MathGeoLib.h"
#include "ComponentRigidbody.h"

ModulePhysics::ModulePhysics(bool active)
{

}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Init()
{
	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	
	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
	world->setGravity(btVector3(0.0f, -5.0f, 0.0f));

	//world->setDebugDrawer(debug_draw);
	gameModule = true;
	return true;
}


update_status ModulePhysics::PreUpdate(float dt)
{
	if(world != nullptr)
		world->stepSimulation(dt, 15);
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update(float dt)
{
	if (world != nullptr)
	{
		world->debugDrawWorld();
	}	
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

btRigidBody* ModulePhysics::AddCubeBody(float mass2, GameObject* go)
{
	btRigidBody* ret = nullptr;

	float mass = mass2;
	OBB box;
	float3 position = float3(go->getPosition().x, go->getPosition().y, go->getPosition().z);
	box.pos = position;
	box.r = float3::one;
	box.axis[0] = float3::unitX;
	box.axis[1] = float3::unitY;
	box.axis[2] = float3::unitZ;


	btCollisionShape* collision_shape = new btBoxShape(btVector3(box.r.x*2,box.r.y*0.1,box.r.z*2));
	shapes.push_back(collision_shape);

	btVector3 local_inertia(0.0f, 0.0f, 0.0f);

	if (mass != 0.0f)
		collision_shape->calculateLocalInertia(mass, local_inertia);


	btDefaultMotionState* def = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo rigidbody_info(mass, def, collision_shape, local_inertia);
	ret = new btRigidBody(rigidbody_info);
	world->addRigidBody(ret);

	
	return ret;
}

bool ModulePhysics::CleanUp()
{
	//RELEASE(world);
	return true;
}




