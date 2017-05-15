#ifndef __ModulePhysics_H__
#define __ModulePhysics_H__

#include "Globals.h"
#include "Module.h"
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

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();


public:

	btDefaultCollisionConfiguration* collision_conf = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btBroadphaseInterface* broad_phase = nullptr;
	btSequentialImpulseConstraintSolver* solver = nullptr;
	btDiscreteDynamicsWorld* world = nullptr;

};

#endif 