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
#include "ModuleAnim.h"

using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	json_parser = new JsonParser(JSONCONFIG);
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(audio = new ModuleAudio());



	// Game Modules
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(animations = new ModuleAnim());
	modules.push_back(scene_intro = new ModuleScene(true));
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
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
	RELEASE(json_parser);
}

bool Application::Init()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	// Start the first scene --
	realTime.start();
	gameTime.start();
	mili.start();
	return ret;

}

update_status Application::Update()
{



	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
	{

		if ((*it)->IsEnabled() == true && !(*it)->fpsDependent)
			ret = (*it)->PreUpdate(dt);
		else
		{
			if ((*it)->IsEnabled() && !(*it)->gameModule)
			{
				ret = (*it)->PreUpdate(dt);
				dtTimer.start();
			}
			else
			{
				ret = (*it)->PreUpdate(dt);
				gameDTimer.start();
			}
		}
	}	
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true && !(*it)->gameModule)
			ret = (*it)->Update(dt);
		else
		{
			if((*it)->IsEnabled() == true && (*it)->oneFramePass == false)
				ret = (*it)->Update(gameDT);
			else
				if ((*it)->oneFramePass == true)
				{
					ret = (*it)->Update(gameDT);

					(*it)->Pause();
					(*it)->oneFramePass = false;
				}
		}
	}
	
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true && !(*it)->fpsDependent)
			ret = (*it)->PostUpdate(dt);
		else
		{
			if ((*it)->IsEnabled() == true && !(*it)->gameModule)
			{
				ret = (*it)->PostUpdate(dt);
				dt = dtTimer.stop();
				frames += 1;
				fps += 1;
			}
			else
			{
				ret = (*it)->PostUpdate(gameDT);
				gameDT = gameDTimer.stop();
			}
			
		}
			
	}
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
	realTime.stop();
	gameTime.stop();
	LOGCHAR("Frames all application: %d ", frames);
	bool ret = true;
	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}




