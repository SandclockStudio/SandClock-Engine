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
	f.horizontalFov = Tan(f.verticalFov / 2) / f.AspectRatio;
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
	f.AspectRatio = newAspectRatio;
	f.verticalFov = 2 * Atan(Tan(f.horizontalFov) * f.AspectRatio);
	//f.horizontalFov = Tan(f.verticalFov / 2) / f.AspectRatio;
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

bool ModuleCamera::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		f.verticalFov = App->json_parser->GetInt("FOVY");
		f.horizontalFov = App->json_parser->GetInt("FOVX");
		f.AspectRatio = App->json_parser->GetFloat("AspectRatio");
		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}
