#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_DEFAULT,

	COLLIDER_MAX
};


struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback;
	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle,COLLIDER_TYPE type, Module* callback = NULL) : // expand this call if you need to
		rect(rectangle) , type(type), callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type, Module* callback = NULL);
	Collider* DeleteCollider(Collider* collider);

	std::list<Collider*> colliders;

private:
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
};

#endif // __ModuleCollision_H__