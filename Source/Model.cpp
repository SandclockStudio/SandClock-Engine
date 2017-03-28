#include "Model.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"


Model::Model()
{
}

Model::~Model()
{
}

void Model::Load(const char * file)
{
	scene = aiImportFile(file, aiProcess_PreTransformVertices | aiProcess_Triangulate);

	ilInit();
	iluInit();
	ilutInit();
	ilClearColour(255, 255, 255, 000);
	ilutRenderer(ILUT_OPENGL);
	ilutEnable(ILUT_OPENGL_CONV);

	index = new unsigned int *[scene->mNumMeshes];
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		index[i] = new unsigned int[3*mesh->mNumFaces];
		unsigned int c = 0;
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			if (mesh->mFaces[j].mNumIndices != 3)
				LOGCHAR("WARNING, geometry face with %d indices, all should be have 3!", mesh->mFaces[j].mNumIndices);
			for (int k = 0; k < 3; ++k, c++)
			{
				//LOGCHAR("mesh->mFaces[%i].mIndices[%i] = %i", j, k, mesh->mFaces[j].mIndices[k]);
				index[i][c] = mesh->mFaces[j].mIndices[k];
				//LOGCHAR(" HOLAAAA index[%i][%i] = %i ", i,c, index[i][c]);
				
			}
		}
		aiString string;
		if (scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &string, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			char* FullPath = string.data;
			GLfloat aux = loadTexture(FullPath);
			textureIndex.push_back(aux);
			LOGCHAR("ESTO ES EL PATH: %s", FullPath);
			LOGCHAR("Index %i: %f", i, aux);
		}

		
	}
}

void Model::Clear()
{
	delete(scene);
	/*for (int i = 0; i< index)
	{
	}*/
	RELEASE_ARRAY(index);
	
}

void Model::DrawDirect()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureIndex[i]);
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
		{
			if ((scene->mMeshes[i]->HasNormals()))
				glNormal3f(scene->mMeshes[i]->mNormals[j].x, scene->mMeshes[i]->mNormals[j].y, scene->mMeshes[i]->mNormals[j].z);
			if ((scene->mMeshes[i]->HasTextureCoords(0)))
				glTexCoord2f((scene->mMeshes[i]->mTextureCoords[0][j].x), (scene->mMeshes[i]->mTextureCoords[0][j].y));

			glVertex3f(scene->mMeshes[i]->mVertices[j].x, scene->mMeshes[i]->mVertices[j].y, scene->mMeshes[i]->mVertices[j].z);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void Model::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[i];
		glEnable(GL_TEXTURE_2D);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		
		glVertexPointer(3, GL_FLOAT, 0, mesh->mVertices);
		glNormalPointer(GL_FLOAT, 0, mesh->mNormals);
		glBindTexture(GL_TEXTURE_2D, textureIndex[i]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(aiVector3D), mesh->mTextureCoords[0]);

		glDrawElements(GL_TRIANGLES,3* mesh->mNumFaces , GL_UNSIGNED_INT, index[i]);

		glBindTexture(GL_TEXTURE_2D, 0);


		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}


// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint Model::loadTexture( char* theFileName)
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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




