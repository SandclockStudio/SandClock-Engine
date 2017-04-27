#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Devil\include\IL\ilut.h"

ComponentCamera::ComponentCamera(bool start_enabled)
{
	//frustum.Type()= PerspectiveFrustum;
	speed = 2.0f;
	rotation_speed = 0.35f;
	frustum.SetPerspective(1.5f, 1.0f);
	Position(float3(0.0f, 0.0f, 0.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);

}

ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::PreUpdate()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*)GetProjectionMatrix());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat*)GetViewMatrix());
	return true;
}

bool ComponentCamera::Update(Frustum f)
{
	//Keyboard
	dt = App->dt;
	movement = float3::zero;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) Position(float3(frustum.Pos().x, frustum.Pos().y + (speed* dt), frustum.Pos().z));
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) Position(float3(frustum.Pos().x, frustum.Pos().y - (speed* dt), frustum.Pos().z));
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) 
		movement += frustum.Front();
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) movement -= frustum.Front();
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) movement += frustum.WorldRight();
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) movement -= frustum.WorldRight();
	frustum.Translate(movement *speed * dt);
	//App->editor->AddLog("Vector movimiento: (%f,%f,%f)", movement.x, movement.y, movement.z);
	//Mouse

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		iPoint motion = App->input->GetMouseMotion();

		float dx = (float)-motion.x * rotation_speed * dt;
		float dy = (float)-motion.y * rotation_speed *dt;
		LookAt(dx, dy);
	}
	return true;
}


void ComponentCamera::LookAt(float dx, float dy)
{
	quaternion = Quat::RotateY(dx);
	frustum.SetFront(quaternion.Mul(frustum.Front()).Normalized());
	frustum.SetUp(quaternion.Mul(frustum.Up()).Normalized());

	quaternion = Quat::RotateAxisAngle(frustum.WorldRight(), dy);
	frustum.SetUp(quaternion.Mul(frustum.Up()).Normalized());
	frustum.SetFront(quaternion.Mul(frustum.Front()).Normalized());
}

void ComponentCamera::Position(float3 pos)
{
	frustum.SetPos(pos); 
}

void ComponentCamera::SetFov(float newFOV)
{
	frustum.SetVerticalFovAndAspectRatio(newFOV*0.0174532925199432957f, frustum.AspectRatio());
	//SetAspectRatio(frustum.AspectRatio());
}

void ComponentCamera::SetAspectRatio(float newAspectRatio)
{
	//frustum.HorizontalFov = 2.f * atanf(tanf(frustum.VerticalFov *0.5) * newAspectRatio);
}

void ComponentCamera::SetPlaneDistances(float _near, float _far)
{
	frustum.SetViewPlaneDistances(_near, _far );
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