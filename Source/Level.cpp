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
	scene = aiImportFile(file, aiProcess_TransformUVCoords | aiProcess_PreTransformVertices | aiProcess_Triangulate);

	root = LoadNode(scene->mRootNode, nullptr);

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

Node* Level::LoadNode(aiNode * node, Node * root)
{

	aiMatrix4x4 mat = node->mTransformation;

	aiVector3D pos = aiVector3D(mat.d2, mat.d3, mat.d4);

	aiQuaternion quat = aiQuaternion();
	quat.w = sqrt(1 + mat.a1 + mat.b2 + mat.c3) / 2;
	quat.x = (mat.c2 - mat.b3) / (4 * quat.w);
	quat.y = (mat.a3 - mat.c1) / (4 * quat.w);
	quat.z = (mat.b1 - mat.a2) / (4 * quat.w);


	Node* nodo;

	bool materialFlag = false;

	GLfloat aux = 0;
	Material mate = Material((int)aux);

	if (node->mMeshes>0)
	{
		aiString string;
		if (scene->mMaterials[scene->mMeshes[node->mMeshes[0]]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &string, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			char* FullPath = string.data;
			aux = loadTexture(FullPath);
			mate.texture = aux;

		}


		aiColor4D ambient;
		aiColor4D diffuse;
		aiColor4D specular;
		aiMaterial* material = scene->mMaterials[scene->mMeshes[0]->mMaterialIndex];

		material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

		if (material->Get(AI_MATKEY_SHININESS, mate.shiness) == AI_SUCCESS)
			mate.shiness *= 128.0f;

		float shine_strength = 1.0f;

		if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shine_strength) == AI_SUCCESS)
			specular *= shine_strength;

		for (int i = 0; i < 3; i++)
		{
			mate.ambient[i] = ambient[i];
			mate.diffuse[i] = diffuse[i];
			mate.specular[i] = specular[i];
		}

		materials.push_back(mate);

		unsigned int* mMeshes = new unsigned int[node->mNumMeshes];
		mMeshes[0] = node->mMeshes[0];

		aiMesh * mesh = scene->mMeshes[node->mMeshes[0]];

		unsigned int * index = new unsigned int[mesh->mNumFaces * 3];
		aiVector3D* auxVertex = new aiVector3D[3 * mesh->mNumVertices];
		aiVector3D* auxNormals = new aiVector3D[2 * mesh->mNumVertices];
		aiVector3D* auxTextCoord = new aiVector3D[2 * mesh->mNumVertices];

		for (int j = 0; j < mesh->mNumVertices; j++)
		{

			if (mesh->HasTextureCoords(0))
			{
				auxTextCoord[j] = aiVector3D(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y, mesh->mTextureCoords[0][j].z);
			}
			else
			{
				materialFlag = false;

			}
			if (mesh->HasNormals())
				auxNormals[j] = aiVector3D(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);

			auxVertex[j] = aiVector3D(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

		}
		unsigned int c = 0;

		for (int k = 0; k < mesh->mNumFaces; k++)
		{
			for (int m = 0; m < 3; ++m, c++)
			{
				index[c] = mesh->mFaces[k].mIndices[m];
			}
		}

		meshes.push_back(My_Mesh((int)aux, auxVertex, auxTextCoord, auxNormals, mesh->mNumVertices, index, mesh->mNumFaces * 3, mesh->mNumFaces));
		nodo = new Node(node->mName, pos, quat, mMeshes, root);
	}

	else
		nodo = new Node(node->mName, pos, quat, root);

	if (node->mNumChildren > 0)
	{
		for (int i = 0; i < node->mNumChildren; i++)
		{
			LinkNode(nodo, LoadNode(node->mChildren[i], nodo));
		}
	}

	return nodo;
}


void Level::Clear()
{
	aiReleaseImport(scene);
}

void Level::Draw()
{

	for (unsigned i = 0; i < meshes.size(); ++i)
	{
		glEnable(GL_TEXTURE_2D);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glBindTexture(GL_TEXTURE_2D, meshes[i].material);
		glNormalPointer(GL_FLOAT, 0, meshes[i].normals);
		glTexCoordPointer(2, GL_FLOAT, sizeof(aiVector3D), meshes[i].tex_coords);
		glVertexPointer(3, GL_FLOAT, 0, meshes[i].vertices);
		glDrawElements(GL_TRIANGLES, meshes[i].num_indices, GL_UNSIGNED_INT, meshes[i].indices);

		glMaterialfv(GL_FRONT, GL_AMBIENT, materials[i].ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[i].diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, materials[i].specular);
		glMaterialf(GL_FRONT, GL_SHININESS, materials[i].shiness);

		glBindTexture(GL_TEXTURE_2D, 0);


		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

Node * Level::FindNode(const char * node)
{
	return nullptr;
}

void Level::LinkNode(Node * node, Node * destination)
{
	destination->childs.push_back(node);
}


// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint Level::loadTexture(char* theFileName)
{

	ILuint imageID;				// Create a image ID as a ULuint

	GLuint textureID;			// Create a texture ID as a GLuint

	ILboolean success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilGenImages(1, &imageID); 		// Generate the image ID

	ilBindImage(imageID); 			// Bind the image

	success = ilLoadImage(theFileName); 	// Load the image file

											// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		// ... then attempt to conver it.
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			//cout << "Image conversion failed - IL reports error: " << error << endl;
			exit(-1);
		}

		// Generate a new texture
		glGenTextures(1, &textureID);

		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_BPP),	// Image colour depth
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Image format (i.e. RGB, RGBA, BGR etc.)
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());			// The actual image data itself
	}
	else // If we failed to open the image file in the first place...
	{
		error = ilGetError();
		//cout << "Image load failed - IL reports error: " << error << endl;
		exit(-1);
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

								 //cout << "Texture creation successful." << endl;

	return textureID; // Return the GLuint to the texture so you can use it!
}