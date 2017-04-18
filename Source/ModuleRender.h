#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	SDL_Renderer* renderer = nullptr;
	SDL_GLContext context;
	int screenWidth = 0;
	int screenHeight = 0;
	int screenSize = 0;
	bool vsync = false;
	int fps_cap = 0;

	

private:
	bool LoadConfig();
};

#endif // __MODULERENDER_H__