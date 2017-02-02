#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

update_status ModuleCamera::Update(float dt)
{
	return update_status();
}

bool ModuleCamera::Start()
{
	return false;
}


bool ModuleCamera::CleanUp()
{
	return false;
}

void ModuleCamera::SetFov()
{
}

void ModuleCamera::SetAspectRatio()
{
}

void ModuleCamera::SetPlaneDistances()
{
}

void ModuleCamera::Position()
{
}

void ModuleCamera::Orientation()
{
}

void ModuleCamera::LookAt()
{
}

void ModuleCamera::GetProjectionMatrix()
{
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
}

void ModuleCamera::GetViewMatrix()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
}
