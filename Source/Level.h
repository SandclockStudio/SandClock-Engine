#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include "Devil\include\IL\ilut.h"

struct Node
{
	aiString name;
	aiVector3D position = aiVector3D(0, 0, 0);
	aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
	unsigned int* meshes;
	Node* parent = nullptr;
	std::vector<Node*> childs;

	Node(aiString name, aiVector3D position, aiQuaternion rotation, unsigned int* meshes, Node* parent = nullptr)
		: name(name), position(position), rotation(rotation),meshes(meshes),parent(parent)
	{}

	Node(aiString name, aiVector3D position, aiQuaternion rotation, Node* parent = nullptr)
		: name(name), position(position), rotation(rotation), parent(parent)
	{
		meshes = nullptr;
	}
};


struct My_Mesh
{
	unsigned material = 0;
	aiVector3D*  vertices;
	aiVector3D* tex_coords;
	aiVector3D* normals;
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
	unsigned num_faces = 0;

	My_Mesh(unsigned material, aiVector3D*  vertices,aiVector3D*  tex_coords, aiVector3D* normals, unsigned num_vertices, unsigned* indices, unsigned num_indices, unsigned num_faces) :
		material(material),vertices(vertices),tex_coords(tex_coords),normals(normals),num_vertices(num_vertices), indices(indices),num_indices(num_indices), num_faces(num_faces)
	{}
};

struct Material
{
	float ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shiness = 0.0f;

public:
	unsigned texture = 0;
	Material(unsigned texture) : texture(texture) {};
};

class Level
{

public:

	Level();
	~Level();

	void Load(const char* file);
	void Clear();
	void Draw();

	unsigned GetNumMeshes() const { return meshes.size(); }
	unsigned GetNumMateriales() const { return materials.size(); }

	My_Mesh& GetMesh(unsigned index) { return meshes[index]; }
	const My_Mesh& GetMesh(unsigned index) const { return meshes[index]; }

	Material& GetMaterial(unsigned index) { return materials[index]; }
	const Material& GetMaterial(unsigned index) const { return materials[index]; }

	Node*  GetRootNode() { return root; }
	const Node* GetRootNode()const { return root; }


	Node* FindNode(const char* node);
	void LinkNode(Node* node, Node* destination);

	Node* LoadNode(aiNode * node,Node * root);

	GLuint loadTexture(char * theFileName);


private:

	Node* root = nullptr;
	std::vector<My_Mesh> meshes;
	std::vector<Material> materials;
	const aiScene* scene = 0;
};

#endif /* _LEVEL_H_ */