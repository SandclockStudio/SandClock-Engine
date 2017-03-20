#include "ComponentTransform.h"

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
	glTranslatef((GLfloat)translation.x, (GLfloat)translation.y, (GLfloat)translation.z);


}

void ComponentTransform::Rotate(aiQuaternion rotation)
{
	//glRotatef((GLfloat)translation.x, (GLfloat)translation.y, (GLfloat)translation.z);

}

void ComponentTransform::Scale(aiVector3D scale)
{
	glScalef((GLfloat)scale.x, (GLfloat)scale.y, (GLfloat)scale.z);

}
