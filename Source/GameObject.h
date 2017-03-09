#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "Component.h"
#include "MathGeoLib.h"

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
			void SetRootNode(GameObject * gameObject) { root = gameObject; }
			aiString GetName(){ return name; }
			void CleanUp();
			void AddComponent(Component* component);
			void DeleteComponent(Component* component);
			GameObject(aiString name, GameObject* root = nullptr)
				: name(name), root(root)
			{}
			bool Update();
			void DrawBoundingBox();
			GameObject* FindGameObject(const char* node);
			void AddChild(GameObject* node, GameObject* destination);
			static GameObject* LoadGameObjectMesh(aiNode * node, aiMesh* mesh,const aiScene* scene);
			static GameObject* LoadGameObject(aiNode * node,const aiScene* scene);
			AABB boundingBox;
			float3* corners = new float3[8];
};
#endif //__GAMEOBJECT_H_