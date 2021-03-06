#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "MyRandom.h"

struct SDL_Texture;


class ModulePlayer : public Module
{
	public:
		ModulePlayer(bool active = true);
		~ModulePlayer();

		bool Start();
		update_status Update(float dt);
		void OnCollision(Collider* c1,Collider* c2);
		bool CleanUp();

	public:
	
		SDL_Texture* graphics = nullptr;	
		Animation* current_animation = nullptr;
		iPoint position;
};

#endif