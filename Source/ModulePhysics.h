#ifndef __ModulePhysics_H__
#define __ModulePhysics_H__

#include "Globals.h"
#include "Bullet\include\btBulletDynamicsCommon.h"
#include "Module.h"
#include "DebugDrawer.h"
#include <vector>
#include "ComponentRigidbody.h"

#ifdef _DEBUG

	#pragma comment (lib, "BulletDynamics_debug.lib")

	#pragma comment (lib, "BulletCollision_debug.lib")

	#pragma comment (lib, "LinearMath_debug.lib")

#else

	#pragma comment (lib, "BulletDynamics.lib")

	#pragma comment (lib, "BulletCollision.lib")

	#pragma comment (lib, "LinearMath.lib")

#endif




struct SDL_Texture;


class ModulePhysics : public Module
{

public:

	ModulePhysics(bool active = true);
	~ModulePhysics();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	btRigidBody * AddCubeBody(float mass2);
	bool CleanUp();


public:

	btDefaultCollisionConfiguration* collision_conf = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btBroadphaseInterface* broad_phase = nullptr;
	btSequentialImpulseConstraintSolver* solver = nullptr;
	btDiscreteDynamicsWorld* world = nullptr;
	DebugDrawer* debug_draw;
	std::vector<btCollisionShape*> shapes;

};

#endif 