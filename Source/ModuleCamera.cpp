#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "JsonParser.h"

ModuleCamera::ModuleCamera()
{
	f.type = PerspectiveFrustum;
}

ModuleCamera::~ModuleCamera()
{
}



bool ModuleCamera::Init()
{
	LoadConfig();
	right = f.WorldRight();
	forward = f.front;
	speed = 1.5f;
	return true;
}
update_status ModuleCamera::Update(float dt)
{



	movement = float3::zero;
	
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) 
	{
		float3 pos = f.pos;
		Position(float3(pos.x, pos.y+ (speed*dt), pos.z));

	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		float3 pos = f.pos;
		Position(float3(pos.x , pos.y - (speed *dt), pos.z));
	}


	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) movement += forward;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) movement -= forward;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) movement += right;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) movement -= right;

	if (movement.Equals(float3::zero) == false)
		f.Translate(movement * dt);

	return UPDATE_CONTINUE;
}

bool ModuleCamera::Start()
{

	return true;
}


bool ModuleCamera::CleanUp()
{
	return true;
}

void ModuleCamera::SetFov(float newFOV)
{
	f.verticalFov = newFOV*0.0174532925199432957f;
	SetAspectRatio(f.AspectRatio());
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
	f.horizontalFov = 2.f * atanf(tanf(f.verticalFov *0.5) * newAspectRatio);
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

void ModuleCamera::LookAt(float3 front, float3 up)
{
	f.front = front;
	f.up = up;
}

float * ModuleCamera::GetProjectionMatrix()
{
	float4x4 m;

	m = f.ProjectionMatrix();
	m.Transpose();

	return (float*)m.v;
}

float * ModuleCamera::GetViewMatrix()
{
	float4x4 m;

	m = f.ViewMatrix();
	m.Transpose();

	return (float*)m.v;
}

bool ModuleCamera::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		/*f.verticalFov = App->json_parser->GetInt("FOVY");
		f.horizontalFov = App->json_parser->GetInt("FOVX");*/
		f.verticalFov = 1.0f;
		f.horizontalFov = 1.5f;
		Position(float3(0.0f, 0.0f, 0.0f));
		LookAt(float3::unitZ,float3::unitY);
		f.nearPlaneDistance = 0.1f;
		f.farPlaneDistance = 1000.0f;
		


		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}


