#ifndef __MODULEEDITOR_H_
#define __MODULEEDITOR_H_

#include "Module.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 
#include "IMGUI\imgui.h"
#include <vector>
#include "GameObject.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();
	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void InputHandler(SDL_Event* event);
	void DrawConsole();
	void DrawFps();
	update_status DrawMenu();
	void AddLog(const char* fmt, ...);
	void AddFps(float fps);
	void DrawTree();
	void Children(GameObject* go, int &ptr_id);
	void DrawProperties();
	void DrawPlayMenu();
public:
	ImGuiTextBuffer Buf;
	std::vector<float> fps_log;
	GameObject* selected = nullptr;


private:
	bool fullscreen;
	bool resizable;

};

#endif // __MODULEEDITOR_H_
