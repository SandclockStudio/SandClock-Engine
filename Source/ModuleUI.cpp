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
	LOGCHAR("Loading fonts");


	return true;
}

update_status ModuleUI::Update(float dt)
{

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	LOGCHAR("Unloading fonts");


	return true;
}

