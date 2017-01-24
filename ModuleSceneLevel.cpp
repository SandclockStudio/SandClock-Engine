#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneLevel.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("");
	App->audio->PlayMusic("", 1.0f);
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	
	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update(float dt)
{
	// Move camera forward -----------------------------


	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}