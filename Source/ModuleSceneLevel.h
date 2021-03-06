#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
};

#endif // __MODULESCENESPACE_H__