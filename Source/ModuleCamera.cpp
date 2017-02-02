#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"


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

float4x4 ModuleCamera::GetProjectionMatrix()
{
	return float4x4();
}

float4x4 ModuleCamera::GetViewMatrix()
{
	return float4x4();
}
