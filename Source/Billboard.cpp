#include "Billboard.h"

Billboard::Billboard()
{
	size = 1.0f;
}

Billboard::~Billboard()
{
	
}

bool Billboard::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	texture = loadImages("billboardgrass.png");
	return true;
}

bool Billboard::Draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, 0.0f);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, size, 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool Billboard::Update()
{
	Draw();
	return true;
}


// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint Billboard::loadImages(const char* theFileName)
{
	ILuint imageId;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);

	if (ilLoadImage(theFileName))
	{
		GLuint textureId = 0;
		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}


		int components = 3;
		int format = GL_RGB;

		switch (ilGetInteger(IL_IMAGE_FORMAT))
		{
		case IL_RGB:
			components = 3;
			format = GL_RGB;
			break;
		case IL_RGBA:
			components = 4;
			format = GL_RGBA;
			break;
		case IL_BGR:
			components = 3;
			format = GL_BGR_EXT;
			break;
		case IL_BGRA:
			components = 4;
			format = GL_BGRA_EXT;
			break;
		default:
			break;
		}

		ILubyte* data = ilGetData();
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int channels = ilGetInteger(IL_IMAGE_CHANNELS);

		if (channels == 3)
			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		else if(channels == 4)
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		glTexImage2D(GL_TEXTURE_2D, 0, components, width,
			height, 0, format,
			GL_UNSIGNED_BYTE, data);

		ilDeleteImages(1, &imageId);

		glBindTexture(GL_TEXTURE_2D, 0);

		return textureId;
	}

	return 0;
}