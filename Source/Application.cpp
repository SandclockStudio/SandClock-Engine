#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
#include "JsonParser.h"
#include "ModuleEditor.h"
#include "ModuleTextures.h"


using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	json_parser = new JsonParser(JSONCONFIG);
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(audio = new ModuleAudio());

	// Game Modules
	modules.push_back(scene_intro = new ModuleScene(false));
	modules.push_back(ui = new ModuleUI());
	modules.push_back(player = new ModulePlayer(false));
	modules.push_back(textures = new ModuleTextures());

	// Modules to draw on top of game LOGCHARic

	modules.push_back(collision = new ModuleCollision());
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(fade = new ModuleFadeToBlack());
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
		App->editor->AddFps(App->fps);
		fps = 0;
	}

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




