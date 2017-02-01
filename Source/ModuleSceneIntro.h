#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Cube.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool active = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	uint fx = 0;
	Cube* c;
	MY::Uint index = 0;
};

#endif // __MODULESCENEINTRO_H__