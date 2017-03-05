#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(bool start_enabled)
{
}

ComponentMaterial::~ComponentMaterial()
{
}

bool ComponentMaterial::Update()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void ComponentMaterial::LoadMaterial(aiMaterial * material)
{
	GLfloat aux = 0;
	aiString string;
	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &string, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
	{
		char* FullPath = string.data;
		aux = loadTexture(FullPath);
		texture = aux;

	}

	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	if (material->Get(AI_MATKEY_SHININESS, shiness) == AI_SUCCESS)
		shiness *= 128.0f;

	float shine_strength = 1.0f;

	if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shine_strength) == AI_SUCCESS)
	{
		specular[0] *= shine_strength;
		specular[1] *= shine_strength;
		specular[2] *= shine_strength;
		specular[3] *= shine_strength;

	}
		

	for (int i = 0; i < 3; i++)
	{
		ambient[i] = ambient[i];
		diffuse[i] = diffuse[i];
		specular[i] = specular[i];
	}
}


// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint ComponentMaterial::loadTexture(char* theFileName)
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

