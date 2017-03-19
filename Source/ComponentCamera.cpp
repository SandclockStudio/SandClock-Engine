#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleInput.h"

ComponentCamera::ComponentCamera(bool start_enabled)
{
	frustum.type = PerspectiveFrustum;
	speed = 2.0f;
	rotation_speed = 0.35f;
	dt = App->dt;
}

ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::PreUpdate()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)GetProjectionMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)GetViewMatrix());
	return true;
}

bool ComponentCamera::Update()
{
	//Keyboard

	
	movement = float3::zero;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) Position(float3(frustum.pos.x, frustum.pos.y + (speed*dt), frustum.pos.z));
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) Position(float3(frustum.pos.x, frustum.pos.y - (speed*dt), frustum.pos.z));
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) movement += frustum.front;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) movement -= frustum.front;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) movement += frustum.WorldRight();
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) movement -= frustum.WorldRight();
	frustum.Translate(movement *speed* dt);

	//Mouse

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint motion = App->input->GetMouseMotion();

		float dx = (float)-motion.x * rotation_speed * dt;
		float dy = (float)-motion.y * rotation_speed * App->dt;
		LookAt(dx, dy);
	}

	return true;
}


void ComponentCamera::LookAt(float xRotation, float yRotation)
{
	quaternion = Quat::RotateY(xRotation);
	frustum.front = quaternion.Mul(frustum.front).Normalized();
	frustum.up = quaternion.Mul(frustum.up).Normalized();

	quaternion = Quat::RotateAxisAngle(frustum.WorldRight(), yRotation);
	frustum.up = quaternion.Mul(frustum.up).Normalized();
	frustum.front = quaternion.Mul(frustum.front).Normalized();
}

void ComponentCamera::Position(float3 pos)
{
	frustum.pos = pos;
}

void ComponentCamera::SetFov(float newFOV)
{
	frustum.verticalFov = newFOV*0.0174532925199432957f;
	SetAspectRatio(frustum.AspectRatio());
}

void ComponentCamera::SetAspectRatio(float newAspectRatio)
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov *0.5) * newAspectRatio);
}

void ComponentCamera::SetPlaneDistances(float _near, float _far)
{
	frustum.farPlaneDistance = _far;
	frustum.nearPlaneDistance = _near;
}

float * ComponentCamera::GetProjectionMatrix()
{
	matrix = frustum.ProjectionMatrix();
	matrix.Transpose();

	return (float*)matrix.v;
}

float * ComponentCamera::GetViewMatrix()
{
	matrix = frustum.ViewMatrix();
	matrix.Transpose();

	return (float*)matrix.v;
}