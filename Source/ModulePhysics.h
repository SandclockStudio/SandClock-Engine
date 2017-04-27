#ifndef __ModulePhysics_H__
#define __ModulePhysics_H__

#include "Globals.h"
#include "Module.h"
#include "../Libraries/Bullet/include/btBulletDynamicsCommon.h"

#ifdef _DEBUG
	#pragma comment (lib,"../Libraries/Bullet/libx86/BulletDynamics_debug.lib")
	#pragma comment (lib,"../Libraries/Bullet/libx86/BulletCollision_debug.lib")
	#pragma comment (lib,"../Libraries/Bullet/libx86/LinearMath_debug.lib")
#else
	#pragma comment (lib,"../Libraries/Bullet/libx86/BulletDynamics.lib")
	#pragma comment (lib,"../Libraries/Bullet/libx86/BulletCollision.lib")
	#pragma comment (lib,"../Libraries/Bullet/libx86/LinearMath.lib")
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