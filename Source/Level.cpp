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

	aiMatrix4x4 mat = scene->mRootNode->mTransformation;
	
	aiVector3D pos = aiVector3D(mat.d2, mat.d3, mat.d4);

	aiQuaternion quat = aiQuaternion();
	quat.w = sqrt(1 + mat.a1 + mat.b2 + mat.c3) / 2;
	quat.x = (mat.c2 - mat.b3) / (4 * quat.w);
	quat.y = (mat.a3 - mat.c1) / (4 * quat.w);
	quat.z = (mat.b1 - mat.a2) / (4 * quat.w);

	/*qw = √(1 + m00 + m11 + m22) / 2
		qx = (m21 - m12) / (4 * qw)
		qy = (m02 - m20) / (4 * qw)
		qz = (m10 - m01) / (4 * qw)*/

	std::vector<unsigned> mMeshes;
	for (int i = 0; i < scene->mRootNode->mNumMeshes;i++)
	{
		mMeshes[i] = scene->mRootNode->mMeshes[i];
	}

	root = new Node(scene->mRootNode->mName, pos, quat, mMeshes, nullptr);


	for (int i = 0; i < scene->mRootNode->mNumChildren; i++)
	{
		
		aiNode* child = scene->mRootNode->mChildren[i];

		aiMatrix4x4 mat = child->mTransformation;

		aiVector3D pos = aiVector3D(mat.d2, mat.d3, mat.d4);

		aiQuaternion quat = aiQuaternion();
		quat.w = sqrt(1 + mat.a1 + mat.b2 + mat.c3) / 2;
		quat.x = (mat.c2 - mat.b3) / (4 * quat.w);
		quat.y = (mat.a3 - mat.c1) / (4 * quat.w);
		quat.z = (mat.b1 - mat.a2) / (4 * quat.w);

		std::vector<unsigned> mMeshes;
		for (int i = 0; i < scene->mRootNode->mNumMeshes; i++)
		{
			mMeshes[i] = scene->mRootNode->mMeshes[i];
		}

		Node* nodo = new Node(child->mName, pos, quat, mMeshes, root);
		root->childs.push_back(nodo);
		
		
	}

	/*
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


	}*/
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
