#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate(float dt)
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update(float dt)
{
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible
	list<Collider*>::iterator iter;
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		Collider* previous = *it;
		iter = it;
		for (++iter; iter != colliders.end(); ++iter)
		{
			Collider* current = *iter;
			if (previous->CheckCollision(current->rect) == true)
			{
				if (matrix[previous->type][current->type] && previous->callback)
					previous->callback->OnCollision(previous, current);

				if (matrix[current->type][previous->type] && current->callback)
					current->callback->OnCollision(current, previous);
			}
		}
	}



	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}


Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect,type,callback);

	colliders.push_back(ret);

	return ret;
}

Collider * ModuleCollision::DeleteCollider(Collider * collider)
{
	if (collider != nullptr)
	{
		colliders.remove(collider);
		RELEASE(collider);
	}

	return nullptr;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if the argument and the own rectangle are intersecting


	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);


}
