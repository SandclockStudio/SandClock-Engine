#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(bool start_enabled)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::LoadTransform(aiNode * node)
{
	mat = node->mTransformation;

	pos = aiVector3D(mat.d2, mat.d3, mat.d4);

	quat = aiQuaternion();
	quat.w = sqrt(1 + mat.a1 + mat.b2 + mat.c3) / 2;
	quat.x = (mat.c2 - mat.b3) / (4 * quat.w);
	quat.y = (mat.a3 - mat.c1) / (4 * quat.w);
	quat.z = (mat.b1 - mat.a2) / (4 * quat.w);
}

void ComponentTransform::Translate(aiVector3D translation)
{
}

void ComponentTransform::Rotate(aiVector3D rotation)
{
}
