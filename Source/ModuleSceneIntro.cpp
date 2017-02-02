#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"


ModuleSceneIntro::ModuleSceneIntro(bool active) : Module(active)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOGCHAR("Loading space intro");
	c = new Cube(0.5f,index);
	p = new MPlane(0.2f, 50, index);
	g = new Gizmo(0.5f, 5.0f, index);

	p->Start();
	c->Start();
	g->Start();

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOGCHAR("Unloading space scene");

	App->textures->Unload(background);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{


	p->DrawDirect();
	c->DrawDirect();
	g->DrawDirect();

	/*

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_level, this);
		App->audio->PlayFx(fx);
	}
	*/

	return UPDATE_CONTINUE;
}