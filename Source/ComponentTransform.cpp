#include "ComponentTransform.h"
#include "GameObject.h"
#include "MathGeoLib.h"

ComponentTransform::ComponentTransform(bool start_enabled)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::LoadTransform(aiNode * node)
{

	node->mTransformation.Decompose(scale, quat, pos);
}

void ComponentTransform::Translate(aiVector3D translation)
{
	pos = translation;
}

void ComponentTransform::Rotate(aiQuaternion rotation)
{
	//glRotatef((GLfloat)translation.x, (GLfloat)translation.y, (GLfloat)translation.z);
}

void ComponentTransform::Scale(aiVector3D scal)
{
	scale = scal;
}

bool ComponentTransform::Update()
{
	glPushMatrix();
	float3 position = float3(pos.x, pos.y, pos.z);
	Quat quaternion = Quat(quat.x,quat.y,quat.z,quat.w);
	float3 scal = float3(scale.x, scale.y, scale.z);

	float* transform = float4x4::FromTRS(position, quaternion, scal).Transposed().ptr();
	glMultMatrixf(transform);

	return true;
}