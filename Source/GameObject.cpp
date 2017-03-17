#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"

void GameObject::CleanUp()
{
	delete(corners);

	for (int i = 0; i < components.size();i++)
	{
		components[i]->CleanUp();
		RELEASE(components[i]);
	}
}

void GameObject::AddComponent(Component * component)
{
	boundingBox = AABB();
	boundingBox.SetNegativeInfinity();
	components.push_back(component);
	component->setGameObject(this);

}


void GameObject::DeleteComponent(Component * component)
{
	/*
	for (int i = 0; i < components.size(); ++i)
	{
		if(components[i]->ID == component->ID)
			components.erase(componentes[i]);
	}
	*/
}

bool GameObject::Update()
{
	for (int i = 0; i < components.size(); ++i)
		components[i]->Update();

	return true;
}

void GameObject::DrawBoundingBox()
{
	
	boundingBox.GetCornerPoints(corners);

	float3 b1 = boundingBox.minPoint;
	float3 b2 = boundingBox.maxPoint;
	float3 b3 = float3(b1.x, b1.y, b2.z);
	float3 b4 = float3(b1.x, b2.y, b1.z);
	float3 b5 = float3(b2.x, b1.y, b1.z);
	float3 b6 = float3(b1.x, b2.y, b2.z);
	float3 b7 = float3(b2.x, b1.y, b2.z);
	float3 b8 = float3(b2.x, b2.y, b1.z);


	glBegin(GL_LINES);

	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b2.x, b2.y, b2.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b8.x, b8.y, b8.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b4.x, b4.y, b4.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b6.x, b6.y, b6.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b3.x, b3.y, b3.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b7.x, b7.y, b7.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b5.x, b5.y, b5.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b1.x, b1.y, b1.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glLineWidth(20.0f);
	glEnd();
}

GameObject * GameObject::FindGameObject(const char * node)
{
	for (int i = 0; i<childs.size(); i++)
		if (strcmp(childs[i]->GetName().C_Str(), node) == 0)
			return childs[i];
	return nullptr;
}

void GameObject::AddChild(GameObject * node, GameObject * destination)
{
	destination->childs.push_back(node);
}

GameObject * GameObject::LoadGameObjectMesh(aiNode * node, aiMesh * mesh, const aiScene * scene)
{
	GameObject * go = new GameObject(node->mName);

	ComponentTransform* transform = new ComponentTransform(true);
	go->AddComponent(transform);
	transform->LoadTransform(node);
	position = transform->pos;
	rotation = transform->quat;
	scale = transform->scale;



	ComponentMaterial* material = new ComponentMaterial(true);
	go->AddComponent(material);
	material->LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
	


	ComponentMesh* m = new ComponentMesh(true);
	go->AddComponent(m);

	m->LoadMesh(mesh, scene);

	return go;
}

GameObject* GameObject::LoadGameObject(aiNode * node, const aiScene* scene)
{
	GameObject * go = new GameObject(node->mName);

	ComponentTransform* transform = new ComponentTransform(true);
	transform->LoadTransform(node);
	go->AddComponent(transform);

	//Si hay mesh, entonces añadimos componente mesh y material
	if (node->mNumMeshes > 0)
	{
		ComponentMesh* mesh = new ComponentMesh(true);
		mesh->LoadMesh(scene->mMeshes[node->mMeshes[0]], scene);
		go->AddComponent(mesh);

		ComponentMaterial* material = new ComponentMaterial(true);
		material->LoadMaterial(scene->mMaterials[scene->mMeshes[node->mMeshes[0]]->mMaterialIndex]);
		go->AddComponent(material);
	}
	 

	return go;
}

aiVector3D GameObject::getPosition()
{
	return position;
}

aiQuaternion GameObject::getRotation()
{
	return rotation;
}

aiVector3D GameObject::getScale()
{
	return scale;
}
