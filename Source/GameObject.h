#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "Component.h"

class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;

class GameObject
{
	private:
			aiString name;
			GameObject* root = nullptr;
			std::vector<GameObject*> childs;
			std::vector<Component*> components;

		

	public:
			GameObject*  GetRootNode() { return root; }
			const GameObject* GetRootNode()const { return root; }
			aiString GetName(){ return name; }
			void AddComponent(Component* component);
			void DeleteComponent(Component* component);
			GameObject(aiString name, GameObject* root = nullptr)
				: name(name), root(root)
			{}
			bool Update();
			GameObject* FindGameObject(const char* node);
			void AddChild(GameObject* node, GameObject* destination);
			
			GameObject* LoadGameObject(aiNode * node,const aiScene* scene);
};
#endif //__GAMEOBJECT_H_