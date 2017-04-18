#ifndef __COMPONENTMESH_H_
#define __COMPONENTMESH_H_

#include "Component.h"
#include <vector>
#include "Globals.h"
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include <assimp/include/assimp/scene.h>


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
	const GameObject *attached_to = nullptr;
};

class ComponentMesh : public Component
{
public:

	ComponentMesh(bool start_enabled = true);
	~ComponentMesh();

	bool Update(Frustum f);
	bool CleanUp();
	void LoadMesh(aiMesh * mesh, const aiScene * scene);

	aiVector3D*  vertices;
	aiVector3D* tex_coords;
	aiVector3D* normals;
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
	unsigned num_faces = 0;
	bool has_bones = false;
	aiVector3D *vertices_skinned;
	std::vector<Bone*> bones;
	//cambiar
	bool playing = true;


	GLuint vbo[4];
	static enum BUFFERS {
		VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
	};
};

#endif // __COMPONENTMESH_