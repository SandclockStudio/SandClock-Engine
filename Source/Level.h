#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include "Devil\include\IL\ilut.h"

class Level
{


	struct Node 
	{
		std::string name;
		aiVector3D position = aiVector3D(0, 0, 0);
		aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
		std::vector<unsigned> meshes;
		Node* parent = nullptr;
		std::vector<Node*> childs;
	};


	struct Mesh
	{
		unsigned material = 0;
		aiVector3D * vertices = nullptr;
		aiVector3D * tex_coords = nullptr;
		aiVector3D * normals = nullptr;
		unsigned num_vertices = 0;
		unsigned* indices;
		unsigned num_indices = 0;
	};

	struct Material
	{
		aiColor4D ambient = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
		aiColor4D diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
		aiColor4D specular = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
		float shiness = 0.0f;
		unsigned texture = 0;
	};




public:

	Level();
	~Level();

	void Load(const char* path, const char* file);
	void Clear();
	void Draw();

	unsigned GetNumMeshes() const { return meshes.size(); }
	unsigned GetNumMateriales() const { return materials.size(); }

	Mesh& GetMesh(unsigned index) { return meshes[index]; }
	const Mesh& GetMesh(unsigned index) const { return meshes[index]; }

	Material& GetMaterial(unsigned index) { return materials[index]; }
	const Material& GetMaterial(unsigned index) const { return materials[index]; }

	Node*  GetRootNode() { return root; }
	const Node* GetRootNode()const { return root; }


	Node* FindNode(const char* node);
	void LinkNode(Node* node, Node* destination);

private:
	Node* root = nullptr;
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
};

#endif /* _LEVEL_H_ */