#include "ComponentMesh.h"
#include "GameObject.h"

ComponentMesh::ComponentMesh(bool start_enabled)
{}

ComponentMesh::~ComponentMesh()
{
}

bool ComponentMesh::Update(Frustum f)
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
	glPopMatrix();
	//myGo->DrawBoundingBox();
	return true;
}

bool ComponentMesh::CleanUp()
{
	RELEASE_ARRAY(vertices);
	RELEASE_ARRAY(normals);
	RELEASE_ARRAY(tex_coords);
	RELEASE_ARRAY(indices);

	if (has_bones)
	{
		for (int i = 0; i < bones.size(); i++)
		{
			RELEASE_ARRAY(bones[i]->weights);
			RELEASE_ARRAY(bones[i]);
		}
		bones.clear();
		
	}
	
		
	

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

		if (mesh->HasBones())
		{
			has_bones = true;
			for (int i = 0; i < mesh->mNumBones; i++)
			{
				aiBone* scene_bone = mesh->mBones[i];
				Bone* bone = new Bone;
				bone->name = scene_bone->mName;

				memcpy(bone->bind.v, &scene_bone->mOffsetMatrix.a1, 16 * sizeof(float));

				bone->num_weights = scene_bone->mNumWeights;
				bone->weights = new Weight[bone->num_weights];
				for (int j = 0; j < bone->num_weights; j++)
				{
					bone->weights[j].weight = scene_bone->mWeights[j].mWeight;
					bone->weights[j].vertex = scene_bone->mWeights[j].mVertexId;
				}
				bones.push_back(bone);
			}
		}

		myGo->boundingBox.Enclose((float3*) vertices, num_vertices);
}



