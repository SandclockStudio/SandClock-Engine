#include "ModulePhysics.h"

ModulePhysics::ModulePhysics(bool active)
{
}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);

	world->setGravity(btVector3(0.0f, -10.0f, 0.0f));


	return true;
}


update_status ModulePhysics::PreUpdate(float dt)
{
	//world->stepSimulation(dt, 15);
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModulePhysics::CleanUp()
{
	//RELEASE(world);
	return true;
}


