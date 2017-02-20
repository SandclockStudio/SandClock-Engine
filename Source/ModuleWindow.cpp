#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include "JsonParser.h"
//#include "SDL/include/SDL_opengl.h"
#include "ModuleEditor.h"

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
	LOGCHAR("Init SDL window & surface");
	bool ret = true;

	if (LoadConfig() == false)
	{
		LOGCHAR("Problem in the configuration file");
		ret = false;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOGCHAR("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = screenWidth * screenSize;
		int height = screenHeight * screenSize;
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |  SDL_WINDOW_RESIZABLE;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(fullScreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		
		window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == nullptr)
		{
			LOGCHAR("Window could not be created! SDL_Error: %s\n", SDL_GetError());
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
	LOGCHAR("Destroying SDL window and quitting all SDL systems");

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

update_status ModuleWindow::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

void ModuleWindow::setFullScreen(bool enable)
{
	if (enable != fullScreen)
	{
		fullScreen = enable;
		if (fullScreen == true)
		{
			if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0)
				App->editor->AddLog("Could not switch to fullscreen: %s\n", SDL_GetError());
			//fullscreen_desktop = false;
			SDL_Log("this is a test");
		}
		else
		{
			if (SDL_SetWindowFullscreen(window, 0) != 0)
				App->editor->AddLog("Could not switch to windowed: %s\n", SDL_GetError());
		}
	}
}

void ModuleWindow::setResizable(bool enable)
{
	resizable = enable;
}