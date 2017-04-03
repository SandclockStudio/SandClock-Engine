#include "Billboard.h"

Billboard::Billboard(int size, float3 pos)
{
	this->size = size;
	this->pos = pos;

	boundingBox = AABB(pos, float3(pos.x + size,pos.y+size,pos.z));
}

Billboard::~Billboard()
{
	
}

bool Billboard::Init()
{
	texture = loadImages("billboardgrass.png");
	return true;
}

bool Billboard::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(positions[3].x, positions[3].y, positions[3].z);
	glTexCoord2d(1.0, 0.0);
	glVertex3f( positions[1].x, positions[1].y, positions[1].z);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(positions[0].x, positions[0].y, positions[0].z);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(positions[3].x, positions[3].y, positions[3].z);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(positions[0].x, positions[0].y, positions[0].z);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(positions[2].x,  positions[2].y, positions[2].z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);


	return true;
}

bool Billboard::Update(Frustum frustum)
{

	ComputeQuad(frustum);

	Draw();
	//DrawBoundingBox();
	return true;
}

void Billboard::ComputeQuad(Frustum frustum)
{
	normal = (frustum.pos - pos);
	up = float3(0, 1, 0);

	right = normal.Cross(up);

	right.Normalize();

	positions[0] = pos + up + right;
	positions[1] = pos - up + right;
	positions[2] = pos + up - right;
	positions[3] = pos - up - right;

}


void Billboard::DrawBoundingBox()
{

	boundingBox = AABB(positions[3], positions[0]);

	float3* corners = new float3[8];
	boundingBox.GetCornerPoints(corners);

	float3 b1 = boundingBox.minPoint;
	float3 b2 = boundingBox.maxPoint;
	float3 b3 = float3(b1.x, b1.y, b2.z);
	float3 b4 = float3(b1.x, b2.y, b1.z);
	float3 b5 = float3(b2.x, b1.y, b1.z);
	float3 b6 = float3(b1.x, b2.y, b2.z);
	float3 b7 = float3(b2.x, b1.y, b2.z);
	float3 b8 = float3(b2.x, b2.y, b1.z);


	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b2.x, b2.y, b2.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b8.x, b8.y, b8.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b4.x, b4.y, b4.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b6.x, b6.y, b6.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b3.x, b3.y, b3.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b7.x, b7.y, b7.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b5.x, b5.y, b5.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b1.x, b1.y, b1.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glLineWidth(20.0f);
	glEnd();
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