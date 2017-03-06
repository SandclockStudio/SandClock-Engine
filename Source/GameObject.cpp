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
	for (int i = 0; i<childs.size(); i++)
		if (strcmp(childs[i]->GetName().C_Str(), node) == 0)
			return childs[i];
	return nullptr;
}

void GameObject::AddChild(GameObject * node, GameObject * destination)
{
	destination->childs.push_back(node);
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
		mesh->LoadMesh(scene->mMeshes[node->mMeshes[0]],scene);
		go->AddComponent(mesh);

		ComponentMaterial* material = new ComponentMaterial(true);
		material->LoadMaterial(scene->mMaterials[scene->mMeshes[node->mMeshes[0]]->mMaterialIndex]);
		go->AddComponent(material);
	}
	 
	//Si tiene hijos entonces le añadimos hijos recursivamente
	if (node->mNumChildren > 0)
	{
		for (int i = 0; i < node->mNumChildren; i++)
		{

			GameObject * child = LoadGameObject(node->mChildren[i], scene);
			go->AddChild(child, go);
			child->SetRootNode(go);
		}
	}

	

	return go;
}
