#include "Model.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include <assimp\include\assimp\scene.h>
#include "../Libraries/OpenGL/include/GL/glew.h"
#include "Globals.h"
#pragma comment (lib, "opengl32.lib") 


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
