#include "Cube.h"
#include "SOIL.h"


Cube::Cube(float size, MY::Uint index) : size(size), index(index)
{}

Cube::~Cube()
{}

void Cube::Translate(GLfloat translation[])
{
	glTranslatef(translation[0], translation[1], translation[2]);
	glPushMatrix();

}

void Cube::Rotate(float angle, GLfloat vector[])
{
	glRotatef(angle, vector[0], vector[1], vector[2]);
	glPushMatrix();
}

void Cube::DrawDirect()
{


	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);




	glBegin(GL_TRIANGLES);

	//front
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

	//up
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, 0); 
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, size, -size); 

	//right
	glTexCoord2d(0.0, 0.0);
	glVertex3f(size, 0, 0); 
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(size, 0.0f, 0.0f); 
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(size, size, 0.0f);

	//left
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size); 
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.0f, size, 0.0f); 

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size); 
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.0f, size,0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, size, -size);

	//Down
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f,0.0f);
	

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f,0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	

	//back
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, -size);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

}
void Cube::Draw()
{

	

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


	//ImageLoad("lena.png"); 

							//front
	GLfloat texVertices[] = { 0,0, 1,0, 1,1, 
							  0,0, 1,1, 0,1, 
							//
							0,0, 1,0, 1,1,
							0,0, 1,1, 0,1,
							//
							0,0, 1,0, 1,1,
							0,0, 1,1, 0,1,
							//
							0,0, 1,0, 1,1,
							0,0, 1,1, 0,1,
							//
							0,0, 1,0, 1,1,
							0,0, 1,1, 0,1,
							//
							0,0, 1,0, 1,1,
							0,0, 1,1, 0,1,
	
	};

	GLfloat texCoords[] = {
		0.0, 0.0,   // texture  face
		1.0, 1.0,
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,


		0.0, 0.0,   // texture  face
		1.0, 1.0,
		1.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,

		0.0, 0.0,   // texture  face
		1.0, 1.0,
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,

		0.0, 0.0,   // texture  face
		1.0, 1.0,
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,

		0.0, 0.0,   // texture  face
		1.0, 1.0,
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,

		0.0, 0.0,   // 
		1.0, 1.0,
		0.0, 1.0,
		1.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,

	};



	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

	


	glBindBuffer(GL_ARRAY_BUFFER, index);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//glBindBuffer(GL_TEXTURE_COORD_ARRAY, texCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 36); //4 puntos por 9 caras

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);


	
}

void Cube::Draw2()
{
	/*GLfloat v0[] = { 0,0,0 };
	GLfloat v1[] = { size,0,0 };
	GLfloat v2[] = { size,size,0 };
	GLfloat v3[] = { 0,size,0 };
	GLfloat v4[] = { 0,size,-size };
	GLfloat v5[] = { 0,0,-size };
	GLfloat v6[] = { size,0,-size };
	GLfloat v7[] = { size,size,-size };*/


	/*GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);*/

	loadImages("lena.png");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	//front
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

	//up
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, size, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0, size, -size);

	//right
	glTexCoord2d(0.0, 0.0);
	glVertex3f(size, 0, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(size, size, 0.0f);

	//left
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.0f, size, 0.0f);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(0.0f, size, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, size, -size);

	//Down
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, 0.0f);


	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, 0.0f, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, 0.0f);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, 0.0f);


	//back
	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, -size);
	glTexCoord2d(1.0, 0.0);
	glVertex3f(size, size, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, -size);

	glTexCoord2d(0.0, 0.0);
	glVertex3f(0.0f, size, -size);
	glTexCoord2d(1.0, 1.0);
	glVertex3f(size, 0.0f, -size);
	glTexCoord2d(0.0, 1.0);
	glVertex3f(0.0f, 0.0f, -size);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Cube::Start()
{

	// cube ///////////////////////////////////////////////////////////////////////
	//    v6----- v5
	//   /|      /|
	//  v1------v0|
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v2------v3

	// 	glBufferData(GL_TEXTURE, sizeof(float)*num_vertices * 2, arrayTextura, GL_STATIC_DRAW);



							//front
	GLfloat vertices1[] = {	0,0,0,				size,0,0,		size,size,0,		//v0-v1-v2
							size,size,0,		0,size,0,		0,0,0,				//V2-V3-V0
							//right
							0,0,0,				0,size,0,		0,size,-size,		//v0-v3-v4
							0,size,-size,		0,0,-size,		0,0,0,				//v4-v5-v0	cre3o que mal v5
							//up
							0,0,0,				0,0,-size,		size,0,-size,		//v0-v5-v6
							size,0,-size,		size,0,0,		0,0,0,				//v6-v1-v0
							//left
							size,0,0,			size,0,-size,	size,size,-size,	//v1,v6,v7	
							size,size,-size,	size,size,0,	size,0,0,			//v7,v2,v1		
							//down
							size,size,-size,	0,size,-size,	0,size,0,			//v7-v4-v3
							0,size,0,			size,size,0,	size,size,-size,	//v3-v2-v7
							//back
							0,size,-size,		size,size,-size, size,0,-size,		//v4-v7-v6
							size,0,-size,		0,0,-size,		0,size,-size		//v6-v5-v4
	};

	//vertices[0] = vertices1[0];



	
	
	glGenBuffers(1, (GLuint*) &(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*108, vertices1, GL_STATIC_DRAW);

	ilInit();
	iluInit();
	ilutInit();
	ilClearColour(255, 255, 255, 000);
	ilutRenderer(ILUT_OPENGL);
	ilutEnable(ILUT_OPENGL_CONV);

	


	//ImageLoad("lena.png");
	img = Cube::loadImages("lena.png");

}


void Cube::ImageLoad(char * imgName)
{
	ilGenImages(1, &imgID); 		// Generate the image ID

	ilBindImage(imgID); 			// Bind the image

	img = ilutGLLoadImage(imgName);

	// Generate a new texture
	glGenTextures(1, &img);

	// Bind the texture to a name
	glBindTexture(GL_TEXTURE_2D, img);

	// Set texture clamping method
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Set texture interpolation method to use linear interpolation (no MIPMAPS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Specify the texture specification
	glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
		0,				// Pyramid level (for mip-mapping) - 0 is the top level
		ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
		ilGetInteger(IL_IMAGE_WIDTH),	// Image width
		ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
		0,				// Border width in pixels (can either be 1 or 0)
		ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
		GL_UNSIGNED_BYTE,		// Image data type
		ilGetData());			// The actual image data itself
}

// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint Cube::loadImages(const char* theFileName)
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

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