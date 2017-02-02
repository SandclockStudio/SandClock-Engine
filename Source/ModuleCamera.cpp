#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"

#include "JsonParser.h"

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

void ModuleCamera::SetFov(float newFOV)
{

	f.verticalFov = newFOV;
	//recalculate horizontal FOV to mantein aspect ratio
	f.horizontalFov = Tan(f.verticalFov / 2) / f.AspectRatio();
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
	
	f.verticalFov = 2 * Atan(Tan(f.horizontalFov) * newAspectRatio);
	//f.horizontalFov = Tan(f.verticalFov / 2) / f.AspectRatio;
}

void ModuleCamera::SetPlaneDistances(float near, float far)
{
	f.farPlaneDistance = far;
	f.nearPlaneDistance = near;
}

void ModuleCamera::Position(float3 pos)
{
	f.pos = pos;
}

void ModuleCamera::Orientation()
{
}

void ModuleCamera::LookAt()
{
}

void ModuleCamera::GetProjectionMatrix()
{
	glGetFloatv(GL_PROJECTION_MATRIX, pm);
}

void ModuleCamera::GetViewMatrix()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, vm);
}

bool ModuleCamera::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		f.verticalFov = App->json_parser->GetInt("FOVY");
		f.horizontalFov = App->json_parser->GetInt("FOVX");
		//f.AspectRatio = App->json_parser->GetFloat("AspectRatio");
		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}
