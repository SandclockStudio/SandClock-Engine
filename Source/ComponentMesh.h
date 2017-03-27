#ifndef __COMPONENTMESH_H_
#define __COMPONENTMESH_H_

#include "Component.h"
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>
#include "MathGeoLib.h"

struct Weight
{
	unsigned vertex = 0;
	float weight = 0.0f;
};

struct Bone
{
	aiString name;
	Weight* weights = nullptr;
	unsigned num_weights = 0;
	float4x4 bind;
};


struct Weight
{
	unsigned vertex = 0;
	float weight = 0.0f;
};

struct Bone
{
	aiString name;
	Weight* weights = nullptr;
	unsigned num_weights = 0;
	float4x4 bind;
};

class ComponentMesh : public Component
{
public:

	ComponentMesh(bool start_enabled = true);
	~ComponentMesh();

	
	bool Update();
	bool CleanUp();
	void LoadMesh(aiMesh * mesh, const aiScene * scene);

	void LoadBones();


	aiVector3D*  vertices;
	aiVector3D* tex_coords;
	aiVector3D* normals;
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
	unsigned num_faces = 0;
	bool has_bones = false;
	std::vector<Bone*> bones;

};

#endif // __COMPONENTMESH_