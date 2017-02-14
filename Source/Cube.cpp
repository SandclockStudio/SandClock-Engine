#include "Cube.h"
#include "SOIL.h"
#include "IL/ilut_config.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"


#pragma comment (lib, "DevIL.lib") 
#pragma comment (lib, "ILU.lib") 
#pragma comment (lib, "ILUT.lib") 
#pragma comment (lib, "assimp-vc140-mt.lib")

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
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, lenaImg);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, lenaImg);*/

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, index);

	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);


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
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	*/
	
}

void Cube::Draw2()
{
	GLfloat v0[] = { 0,0,0 };
	GLfloat v1[] = { size,0,0 };
	GLfloat v2[] = { size,size,0 };
	GLfloat v3[] = { 0,size,0 };
	GLfloat v4[] = { 0,size,-size };
	GLfloat v5[] = { 0,0,-size };
	GLfloat v6[] = { size,0,-size };
	GLfloat v7[] = { size,size,-size };


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



	
	
	glGenBuffers(1, (GLuint*) &(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*108, vertices1, GL_STATIC_DRAW);
	


	ilInit();
	iluInit();
	ilutInit();
	ilClearColour(255, 255, 255, 000);
	ilutRenderer(ILUT_OPENGL);
	ilutEnable(ILUT_OPENGL_CONV);

	lenaImg = ilutGLLoadImage("lena.png");

}
