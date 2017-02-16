#ifndef __MODULEEDITOR_H_
#define __MODULEEDITOR_H_

#include "Module.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 

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

public:
	void InputHandler(SDL_Event* event);

private:
	
};

#endif // __MODULEEDITOR_H_
