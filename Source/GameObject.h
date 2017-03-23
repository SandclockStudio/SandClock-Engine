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
			bool inFrustum;


			aiVector3D position;
			aiQuaternion rotation;
			aiVector3D scale;

	public:
			GameObject*  GetRootNode() { return root; }
			const GameObject* GetRootNode()const { return root; }
			std::vector<GameObject*> getChilds() { return childs; }
			void SetRootNode(GameObject * gameObject) { root = gameObject; }
			aiString GetName(){ return name; }
			void CleanUp();
			void AddComponent(Component* component);
			void DeleteComponent(Component* component);
			bool Update();
			GameObject(aiString name, GameObject* root = nullptr)
				: name(name), root(root)
			{};
			bool PreUpdate();
			void DrawBoundingBox();
			GameObject* FindGameObject(const char* node);
			void AddChild(GameObject* node, GameObject* destination);
			GameObject* LoadGameObjectMesh(aiNode * node, aiMesh* mesh,const aiScene* scene);
			GameObject* LoadGameObject(aiNode * node,const aiScene* scene);
			aiVector3D getPosition();
			aiQuaternion getRotation();
			aiVector3D getScale();

			void DrawLines();

			void setPosition(aiVector3D newPosition);

			void setRotation(aiQuaternion newRotation);

			void setScale(aiVector3D newScale);

			bool intersectFrustumAABB(Frustum f, AABB b);




			AABB boundingBox;
			float3* corners = new float3[8];
			
			std::vector<Component*> components;
			
};
#endif //__GAMEOBJECT_H_