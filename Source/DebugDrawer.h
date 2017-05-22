#ifndef __DebugDrawer__
#define __DebugDrawer__


#include "Bullet\include\btBulletDynamicsCommon.h"

#ifdef _DEBUG

#pragma comment (lib, "BulletDynamics_debug.lib")

#pragma comment (lib, "BulletCollision_debug.lib")

#pragma comment (lib, "LinearMath_debug.lib")

#else

#pragma comment (lib, "BulletDynamics.lib")

#pragma comment (lib, "BulletCollision.lib")

#pragma comment (lib, "LinearMath.lib")

#endif



class DebugDrawer : public btIDebugDraw
{
public:
	DebugDrawer() {}
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
};


#endif 