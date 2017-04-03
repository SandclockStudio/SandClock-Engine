#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleAudio.h"
#include "ModuleUI.h"

ModulePlayer::ModulePlayer(bool active) : Module(active)
{}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOGCHAR("Loading player");


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOGCHAR("Unloading player");

	App->textures->Unload(graphics);

	return true;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	// Draw everything --------------------------------------

	

	return UPDATE_CONTINUE;
}
