#include "ComponentTransform.h"
#include "GameObject.h"


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

	quat = rotation;
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

bool ComponentTransform::Update(Frustum f)
{

		float3 position = float3(pos.x, pos.y, pos.z);
		Quat quaternion = Quat(quat.x, quat.y, quat.z, quat.w);
		float3 scal = float3(scale.x, scale.y, scale.z);
		float3 euler = quaternion.ToEulerXYZ() * 180.0f / pi;
		float3 posAux = float3(myGo->getPosition().x, myGo->getPosition().y, myGo->getPosition().z);
		//glTranslatef(-posAux.x, -posAux.y, -posAux.z);
		glRotatef(euler.x, 1, 0, 0);
		glRotatef(euler.y, 0, 1, 0);
		glRotatef(euler.z, 0, 0, 1);
		glTranslatef(posAux.x, posAux.y, posAux.z);
		
		glTranslatef(position.x, position.y, position.z);
	
		glScalef(scale.x, scale.y, scale.z);
		
		

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

	return true;
}

