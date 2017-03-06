#ifndef __COMPONENTMESH_H_
#define __COMPONENTMESH_H_

#include "Component.h"
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>


class ComponentMesh : public Component
{
public:

	ComponentMesh(bool start_enabled = true);
	~ComponentMesh();

	
	bool Update();

	void LoadMesh(aiMesh * mesh, const aiScene * scene);

private:
	aiVector3D*  vertices;
	aiVector3D* tex_coords;
	aiVector3D* normals;
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
	unsigned num_faces = 0;
	unsigned texture = 0;
};

#endif // __COMPONENTMESH_