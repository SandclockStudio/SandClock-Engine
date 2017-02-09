#include "Cube.h"

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


}

void Cube::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices * 3);
	glDisableClientState(GL_VERTEX_ARRAY);

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

	/*
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

void Cube::Start()
{
						//1
	GLfloat vertices[] = {0,0,0,
						 size,0,0, 
						 size,size,0,
						//2
						 0,0,0,
						 size,size,0,
						 0,size,0,
						//3
						 0,size,0,
						 size,size,0,
						 size,size,-size,
						//4
						 0,size,0,
						 size,size,-size,
						 0,size,-size,
						//5
						 size,0,0,
						 size,0,-size,
						 size,size,-size,
						//6
						 size,0,0,
						 size,size,-size,
						 size,size,0,
						//7 
						0,0,-size,
						0,0,0,
						0,size,0,
						//8
						0,0,-size,
						0,size,0,
						0,size,-size,
						//9
						0,0,-size,
						size,0,-size,
						size,0,0,
						//10
						0,0,-size,
						size,0,0,
						0,0,0,
						//11
						0,size,-size,
						size,size,-size,
						size,0,-size,
						//12
						0,size,-size,
						size,0,-size,
						0,0,-size
						};

	
	glGenBuffers(1, (GLuint*) &(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_vertices * 3, vertices, GL_STATIC_DRAW);
}
