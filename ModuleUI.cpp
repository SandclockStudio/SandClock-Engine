#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleSceneLevel.h"

ModuleUI::ModuleUI(bool active)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	LOG("Loading fonts");

	ui = App->textures->Load("");

	return true;
}

update_status ModuleUI::Update()
{

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading fonts");


	return true;
}

