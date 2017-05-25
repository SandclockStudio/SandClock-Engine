#include "../Libraries/OpenGL/include/GL/glew.h"
#include "ComponentMesh.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleAnim.h"
#pragma comment(lib, "ProfilerCore64.lib")
#include "Brofiler\Brofiler.h"



ComponentMesh::ComponentMesh(bool start_enabled)
{
	BROFILER_FRAME("Component_Mesh")
}

ComponentMesh::~ComponentMesh()
{
	if(vertices_skinned != nullptr)
		delete(vertices_skinned);
}

bool ComponentMesh::Update2(Frustum f)
{
	glBindVertexArray(vao);
	BROFILER_CATEGORY("Update Mesh 2", Profiler::Color::Black);
	if (has_bones)
	{
		if (App->animations->IsEnabled())
		{
			vertices_skinned = new float3[num_vertices];
			memset(vertices_skinned, 0, num_vertices * sizeof(float3));
			float4x4 mat = float4x4::identity;
			for (unsigned int b = 0; b < bones.size(); ++b)
			{
				mat = bones[b]->attached_to->GetModelSpaceTransformMatrix() * bones[b]->bind;
				for (unsigned int w = 0; w < bones[b]->num_weights; ++w)
				{
					float3 temp = bones[b]->weights[w].weight * mat.TransformPos(float3(vertices[bones[b]->weights[w].vertex].x, vertices[bones[b]->weights[w].vertex].y, vertices[bones[b]->weights[w].vertex].z));
					vertices_skinned[bones[b]->weights[w].vertex] += temp;
					//	vertices_skinned[m_bones[b].weights[w].vertex] += m_bones[b].weights[w].weight * (mat * vertices[m_bones[b].weights[w].vertex].ToPos4()).Float3Part();
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vertices_skinned[0]), &vertices_skinned[0], GL_DYNAMIC_DRAW);
		}
	}

	if (vbo[VERTEX_BUFFER]) {
		//glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	}

	if (vbo[TEXCOORD_BUFFER]) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
		//glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	}

	if (vbo[NORMAL_BUFFER]) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, 0);
	}


	if (vbo[INDEX_BUFFER]) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);

	}

	glBindVertexArray(0);
	glPopMatrix();
	return true;
}

bool ComponentMesh::Update(Frustum f)
{
	BROFILER_CATEGORY("Update Mesh1", Profiler::Color::Black);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(3, GL_FLOAT, sizeof(float3), tex_coords);
	
	if (has_bones)
	{
		if(App->animations->IsEnabled())
		{
			RecalculateBonesInMesh();
		}

		glVertexPointer(3, GL_FLOAT, 0, &vertices_skinned[0]);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
		glBindTexture(GL_TEXTURE_2D, 0);
		//RELEASE(vertices_skinned);
	}
	else
	{
		
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);
		glBindTexture(GL_TEXTURE_2D,0);
		
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

	//myGo->DrawBoundingBox();
	return true;
}

void ComponentMesh::RecalculateBonesInMesh()
{
	BROFILER_CATEGORY("Recalculate Bones", Profiler::Color::Chocolate);
	vertices_skinned = new float3[num_vertices];
	memset(vertices_skinned, 0, num_vertices * sizeof(float3));
	float4x4 mat = float4x4::identity;
	for (size_t b = 0; b < bones.size(); ++b)
	{
		BROFILER_CATEGORY("In loop 1", Profiler::Color::Chocolate);
		mat = bones[b]->attached_to->GetModelSpaceTransformMatrix() * bones[b]->bind;
		for (size_t w = 0; w < bones[b]->num_weights; ++w)
		{
			BROFILER_CATEGORY("In loop 2", Profiler::Color::Chocolate);
			vertices_skinned[bones[b]->weights[w].vertex] += bones[b]->weights[w].weight * mat.TransformPos(float3(vertices[bones[b]->weights[w].vertex].x, vertices[bones[b]->weights[w].vertex].y, vertices[bones[b]->weights[w].vertex].z));
			//	vertices_skinned[m_bones[b].weights[w].vertex] += m_bones[b].weights[w].weight * (mat * vertices[m_bones[b].weights[w].vertex].ToPos4()).Float3Part();
		}
	}
}

bool ComponentMesh::CleanUp()
{
	RELEASE_ARRAY(vertices);
	RELEASE_ARRAY(normals);
	RELEASE_ARRAY(tex_coords);
	RELEASE_ARRAY(indices);

	if (has_bones)
	{
		for (unsigned int i = 0; i < bones.size(); i++)
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

	BROFILER_CATEGORY("LoadMesh", Profiler::Color::Black);
	indices = new unsigned int[mesh->mNumFaces * 3];
	vertices = new float3[3 * mesh->mNumVertices];
	normals = new float3[2 * mesh->mNumVertices];
	tex_coords = new float3[2 * mesh->mNumVertices];
	num_indices = mesh->mNumFaces * 3;
	num_vertices = mesh->mNumVertices;
	componentType = MESH;
	
	vbo[VERTEX_BUFFER] = NULL;
	vbo[TEXCOORD_BUFFER] = NULL;
	vbo[NORMAL_BUFFER] = NULL;
	vbo[INDEX_BUFFER] = NULL;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	if (mesh->HasPositions())
	{
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			vertices[j] = float3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
		}

		glGenBuffers(1, &vbo[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if (mesh->HasTextureCoords(0))
	{
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			tex_coords[j] = float3(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y, mesh->mTextureCoords[0][j].z);
		}

		glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), tex_coords, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

	}

	if (mesh->HasNormals())
	{
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			normals[j] = float3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
		}
		glGenBuffers(1, &vbo[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), normals, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);
	}

	if (mesh->HasFaces())
	{
		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			indices[j * 3] = mesh->mFaces[j].mIndices[0];
			indices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
			indices[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
		}
		glGenBuffers(1, &vbo[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(3);
	}

	

	if (mesh->HasBones())
	{
		has_bones = true;
			
		for (unsigned int i = 0; i < mesh->mNumBones; i++)
		{
			aiBone* scene_bone = mesh->mBones[i];
			Bone* bone = new Bone;

			bone->name = scene_bone->mName;

			memcpy(bone->bind.v, &scene_bone->mOffsetMatrix.a1, 16 * sizeof(float));

			bone->num_weights = scene_bone->mNumWeights;
			bone->weights = new Weight[bone->num_weights];
			for (unsigned int j = 0; j < bone->num_weights; j++)
			{
				bone->weights[j].weight = scene_bone->mWeights[j].mWeight;
				bone->weights[j].vertex = scene_bone->mWeights[j].mVertexId;
			}
			bones.push_back(bone);
		}
	}

	myGo->boundingBox.Enclose((float3*) vertices, num_vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}



