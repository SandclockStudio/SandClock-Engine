#include "Model.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include <assimp\include\assimp\scene.h>
#include "../Libraries/OpenGL/include/GL/glew.h"
#include "Globals.h"
#pragma comment (lib, "opengl32.lib") 
#include <iostream>


Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const char * file)
{
	scene = aiImportFile(file, aiProcess_TransformUVCoords | aiProcess_PreTransformVertices);
}

void Model::Clear()
{
	delete(scene);
}

void Model::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
		{
			glColor3f(1.0f, 1.0f, 1.0f);
			/*if ((scene->mMeshes[i]->HasTextureCoords(j)))
				glTexCoord2f(scene->mMeshes[i]->mTextureCoords[j]->x, scene->mMeshes[i]->mTextureCoords[j]->y);*/
			if ((scene->mMeshes[i]->HasNormals()))
				glNormal3f(scene->mMeshes[i]->mNormals[j].x, scene->mMeshes[i]->mNormals[j].y, scene->mMeshes[i]->mNormals[j].z);

			glVertex3f(scene->mMeshes[i]->mVertices[j].x, scene->mMeshes[i]->mVertices[j].y, scene->mMeshes[i]->mVertices[j].z);



		}
	}
	glEnd();

}

void Model::Draw2() 
{
	// Read our .obj file
	std::vector<unsigned short> indices;
	std::vector<math::vec> vertices;
	std::vector<math::float2> uvs;
	std::vector<math::vec> normals; // Won't be used at the moment.
	LoadAssimp("Batman.obj", indices, vertices, uvs, normals);
}


void Model::LoadAssimp(const char * path, std::vector<unsigned short> & indices,  std::vector<math::vec> & vertices, std::vector<math::float2> & uvs, std::vector<math::vec> & normals)
{


	//Load path in the scene
		Load(path);


		const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

												// Fill vertices positions
		vertices.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
			aiVector3D pos = mesh->mVertices[i];
			vertices.push_back(math::vec(pos.x, pos.y, pos.z));
		}

		// Fill vertices texture coordinates
		uvs.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
			aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
			uvs.push_back(math::float2(UVW.x, UVW.y));
		}

		// Fill vertices normals
		normals.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			normals.push_back(math::vec(n.x, n.y, n.z));
		}


		// Fill face indices
		indices.reserve(3 * mesh->mNumFaces);
		for (unsigned int i = 0; i<mesh->mNumFaces; i++) {
			// Assume the model has only triangles.
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);
		}

		// The "scene" pointer will be deleted automatically by "importer"

}
