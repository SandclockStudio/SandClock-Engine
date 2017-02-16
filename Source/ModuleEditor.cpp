#include "Application.h"
#include "JsonParser.h"
#include "ModuleEditor.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_sdl_gl3.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 
#include "ModuleWindow.h"


ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	ImGui_ImplSdlGL3_Init(App->window->window);
	return true;
}

update_status ModuleEditor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);

	return update_status();
}

update_status ModuleEditor::Update(float dt)
{
	ImGui::ShowTestWindow();
	return update_status();
}

update_status ModuleEditor::PostUpdate(float dt)
{
	//ImGui::ShowTestWindow();

	return update_status();
}


bool ModuleEditor::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

void ModuleEditor::InputHandler(SDL_Event* event)
{
	ImGui_ImplSdlGL3_ProcessEvent(event);
}
