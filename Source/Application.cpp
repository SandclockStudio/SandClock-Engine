#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneLevel.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "JsonParser.h"
#include "ModuleCamera.h"


using namespace std;

Application::Application()
{
	
	
	// Order matters: they will init/start/pre/update/post in this order
	json_parser = new JsonParser(JSONCONFIG);
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	// Game Modules
	modules.push_back(scene_intro = new ModuleSceneIntro(false));
	modules.push_back(scene_level = new ModuleSceneLevel(false));
	modules.push_back(ui = new ModuleUI());
	modules.push_back(player = new ModulePlayer(false));

	// Modules to draw on top of game LOGCHARic
	modules.push_back(collision = new ModuleCollision());
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(fade = new ModuleFadeToBlack());
	modules.push_back(camera = new ModuleCamera());

	
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
	RELEASE(json_parser);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	// Start the first scene --
	fade->FadeToBlack(scene_intro, nullptr, 3.0f);
	mili.start();
	return ret;
	
}

update_status Application::Update()
{

	dtTimer.start();

	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate(dt);

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update(dt);

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate(dt);

	dt = dtTimer.stop();
	frames += 1;
	fps += 1;

	if (mili.read() >= 1000.0f)
	{
		mili.stop();
		sprintf(newTitle, "%s -- %i", window->title, App->fps);
		SDL_SetWindowTitle(window->window, newTitle);
		mili.start();
		fps = 0;
	}

	//Event handler from the window
	EventHandler();

	return ret;
}

bool Application::CleanUp()
{
	LOGCHAR("Frames all application: %d ", frames);
	bool ret = true;
	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

void Application::EventHandler()
{
	Uint32 windowID = SDL_GetWindowID(App->window->window);
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) 
		{

			case SDL_WINDOWEVENT: 
			{
				if (event.window.windowID == windowID) 
				{
					switch (event.window.event)
					{

						case SDL_WINDOWEVENT_RESIZED:
						{
							App->window->screenWidth = event.window.data1;
							App->window->screenHeight = event.window.data2;
							break;
						}
					}
				}
				break;
			}
		}
	}

}



