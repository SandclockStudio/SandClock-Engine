#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "JsonParser.h"

ModuleWindow::ModuleWindow()
{
	
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (LoadConfig() == false)
	{
		LOG("Problem in the configuration file");
		ret = false;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = screenWidth * screenSize;
		int height = screenHeight * screenSize;
		Uint32 flags = SDL_WINDOW_SHOWN;

		if(fullScreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != nullptr)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

bool ModuleWindow::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		title = App->json_parser->GetString("Title") ;
		screenWidth = App->json_parser->GetInt("Width");
		screenHeight = App->json_parser->GetInt("Height");
		screenSize = App->json_parser->GetInt("Size");
		fullScreen = App->json_parser->GetBool("Fullscreen");
		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}
