#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	update_status Update(float dt);


public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;


	const char* title = "";
	int screenWidth = 0;
	int screenHeight = 0;
	int screenSize = 0;
	bool fullScreen = false;

private:
	bool LoadConfig();
};

#endif // __MODULEWINDOW_H__