#include "ComponentMesh.h"
#include "Application.h"



#include "ModuleTextures.h"

ComponentMesh::ComponentMesh(bool start_enabled)
{
}

ComponentMesh::~ComponentMesh()
{
}

bool ComponentMesh::Update()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, sizeof(aiVector3D),tex_coords);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	return true;
}

void ComponentMesh::LoadMesh(aiMesh* mesh, const aiScene* scene)
{

		GLfloat aux = 0;
		aiString string;
		if (scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &string, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			char* FullPath = string.data;
			aux = App->textures->loadTexture(FullPath);
			texture = aux;
		}


		indices = new unsigned int[mesh->mNumFaces * 3];
		vertices = new aiVector3D[3 * mesh->mNumVertices];
		normals = new aiVector3D[2 * mesh->mNumVertices];
		tex_coords = new aiVector3D[2 * mesh->mNumVertices];
		num_indices = mesh->mNumFaces * 3;

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
}


