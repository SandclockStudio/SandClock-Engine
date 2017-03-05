#ifndef __COMPONENTMESH_H_
#define __COMPONENTMESH_H_

#include "Component.h"



class ComponentMesh : public Component
{
public:

	ComponentMesh(bool start_enabled = true);
	~ComponentMesh();

	
	bool Update();

	void LoadMesh(aiMesh* mesh);

private:
	aiVector3D*  vertices;
	aiVector3D* tex_coords;
	aiVector3D* normals;
	unsigned num_vertices = 0;
	unsigned* indices;
	unsigned num_indices = 0;
	unsigned num_faces = 0;
};

#endif // __COMPONENTMESH_