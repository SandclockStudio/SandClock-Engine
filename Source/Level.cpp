#include "Level.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Load(const char * file)
{
	scene = aiImportFile(file, aiProcess_TransformUVCoords | aiProcess_PreTransformVertices);
	
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh * mesh = scene->mMeshes[i];
		aiVector3D* auxVertex;
		aiVector3D* auxNormals;
		aiVector2D* auxTextCoord;

		unsigned int * index;
		unsigned int aux = 0;

		for (int j = 0; j < mesh->mNumVertices; j++)
		{
			auxVertex = new aiVector3D(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
			auxTextCoord = new aiVector2D(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			auxNormals = new aiVector3D(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
		}
		for (int k = 0; k < mesh->mNumFaces; k++)
		{	
			unsigned int c = 0;
			for (int m = 0; m < 3; m++,c++)
			{
				index[c] = mesh->mFaces[k].mIndices[m];

			}
		}
		
		meshes.push_back(My_Mesh(mesh->mMaterialIndex, auxVertex, auxTextCoord,auxNormals, mesh->mNumVertices,index,sizeof(index)));


	}
}

void Level::Clear()
{
	aiReleaseImport(scene);
}

void Level::Draw()
{

}

Node * Level::FindNode(const char * node)
{
	return nullptr;
}

void Level::LinkNode(Node * node, Node * destination)
{

}
