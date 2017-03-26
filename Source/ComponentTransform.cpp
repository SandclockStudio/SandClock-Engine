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

	/*for (int i = 0; myGo->getChilds().size(); i++)
	{
		if (myGo->getChilds()[i]->components[0] != nullptr)
			dynamic_cast<ComponentTransform*>(myGo->getChilds()[i]->components[0])->Scale(scal);
	}*/
}

bool ComponentTransform::Update()
{
	aiString camera = aiString("Camera");

	if (myGo->GetName() != camera)
	{
		glPushMatrix();
		float3 position = float3(pos.x, pos.y, pos.z);
		Quat quaternion = Quat(quat.x, quat.y, quat.z, quat.w);
		float3 scal = float3(scale.x, scale.y, scale.z);
		float3 euler = quaternion.ToEulerXYZ() * 180.0f / pi;

		glTranslatef(position.x, position.y, position.z);
		glRotatef(euler.x, 1, 0, 0);
		glRotatef(euler.y, 0, 1, 0);
		glRotatef(euler.z, 0, 0, 1);
		glScalef(scale.x, scale.y, scale.z);
		glPopMatrix();
		//float* transform = float4x4::FromTRS(position, quaternion, scal).Transposed().ptr();
	}


	return true;
}
bool ComponentTransform::Update2()
{

	
		float3 position = float3(pos.x, pos.y, pos.z);
		Quat quaternion = Quat(quat.x, quat.y, quat.z, quat.w);
		float3 scal = float3(scale.x, scale.y, scale.z);
		float3 euler = quaternion.ToEulerXYZ() * 180.0f / pi;

		glTranslatef(position.x, position.y, position.z);
		glRotatef(euler.x, 1, 0, 0);
		glRotatef(euler.y, 0, 1, 0);
		glRotatef(euler.z, 0, 0, 1);
		glScalef(scal.x, scal.y, scal.z);
		//float* transform = float4x4::FromTRS(position, quaternion, scal).Transposed().ptr()

	return true;
}

