#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleScene.h"

ModuleUI::ModuleUI(bool active)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	return true;
}


update_status ModuleUI::Update(float dt)
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// args: left, right, bottom, top, near, far
	glOrtho(0.0f, 640, 480, 0.0f, 1.0f, -1.0f);

	for (int i = 0; i < App->scene_intro->gameObject.size(); ++i)
	{
		if (App->scene_intro->gameObject[i]->getRenderType() == RenderType::UIRENDER)
		{
			App->scene_intro->gameObject[i]->UpdateUI();
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return true;
}

