#include "ComponentMesh.h"
#include "MathGeoLib.h"
#include "GameObject.h"
#include "ComponentTransform.h"

ComponentMesh::ComponentMesh(bool start_enabled)
{}

ComponentMesh::~ComponentMesh()
{
}

bool ComponentMesh::Update()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(3, GL_FLOAT, sizeof(aiVector3D),tex_coords);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
	glBindTexture(GL_TEXTURE_2D,0);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	myGo->DrawBoundingBox();
	glPopMatrix();
	return true;
}

bool ComponentMesh::CleanUp()
{
	RELEASE_ARRAY(vertices);
	RELEASE_ARRAY(normals);
	RELEASE_ARRAY(tex_coords);
	RELEASE_ARRAY(indices);
	return true;
}

void ComponentMesh::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	indices = new unsigned int[mesh->mNumFaces * 3];
	vertices = new aiVector3D[3 * mesh->mNumVertices];
	normals = new aiVector3D[2 * mesh->mNumVertices];
	tex_coords = new aiVector3D[2 * mesh->mNumVertices];
	num_indices = mesh->mNumFaces * 3;
	num_vertices = mesh->mNumVertices;
	componentType = MESH;
	for (int j = 0; j < mesh->mNumVertices; j++)
	{
		if (mesh->HasTextureCoords(0))
			tex_coords[j] = aiVector3D(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y, mesh->mTextureCoords[0][j].z);

		if (mesh->HasNormals())
			normals[j] = aiVector3D(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

		vertices[j] = aiVector3D(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
	}

		unsigned int c = 0;
		for (int k = 0; k < mesh->mNumFaces; k++)
		{
			for (int m = 0; m < 3; ++m, c++)
			{
				indices[c] = mesh->mFaces[k].mIndices[m];
			}
		}

		myGo->boundingBox.Enclose((float3*) vertices, num_vertices);
}


