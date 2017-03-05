#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"


void GameObject::AddComponent(Component * component)
{
	components.push_back(component);
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

GameObject * GameObject::FindGameObject(const char * node)
{
	return nullptr;
}

void GameObject::AddChild(GameObject * node, GameObject * destination)
{
	destination->childs.push_back(node);
}

GameObject* GameObject::LoadGameObject(aiNode * node, const aiScene* scene)
{

	ComponentMaterial* material =  new ComponentMaterial(true);
	ComponentMesh* mesh = new ComponentMesh(true);
	ComponentTransform* transform = new ComponentTransform(true);

	material->LoadMaterial(scene->mMaterials[scene->mMeshes[node->mMeshes[0]]->mMaterialIndex]);
	mesh->LoadMesh(scene->mMeshes[node->mMeshes[0]]);
	transform->LoadTransform(node);

	return this;
}
