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
	g = new Gizmo(0.5f, 2.0f, index);
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
	GLfloat translate[] = { -0.5f,0,-2.0f };
	c->Translate(translate);
	GLfloat vector[] = { 1,1,0 };
	c->Rotate(angle, vector);
	angle++;
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