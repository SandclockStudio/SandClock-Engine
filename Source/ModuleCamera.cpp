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
	speed = 1.5f;
	rotation_speed = 0.35f;
	return true;
}
update_status ModuleCamera::Update(float dt)
{

	//Keyboard
	movement = float3::zero;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) Position(float3(f.pos.x, f.pos.y+ (speed*dt), f.pos.z));
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) Position(float3(f.pos.x , f.pos.y - (speed *dt), f.pos.z));
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) movement += f.front;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) movement -= f.front;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) movement += f.WorldRight();
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) movement -= f.WorldRight();
	f.Translate(movement * dt);

	//Mouse

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint motion = App->input->GetMouseMotion();

		float dx = (float)-motion.x * rotation_speed * dt;
		float dy = (float)-motion.y * rotation_speed * dt;
		LookAt(dx, dy);
	}
	
	

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

void ModuleCamera::LookAt(float xRotation, float yRotation)
{
	Quat q = Quat::RotateY(xRotation);
	f.front = q.Mul(f.front).Normalized();
	f.up = q.Mul(f.up).Normalized();

	q = Quat::RotateAxisAngle(f.WorldRight(), yRotation);
	f.up = q.Mul(f.up).Normalized();
	f.front = q.Mul(f.front).Normalized();
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
		f.front = float3::unitZ;
		f.up = float3::unitY;
		f.nearPlaneDistance = 0.1f;
		f.farPlaneDistance = 1000.0f;

		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}


