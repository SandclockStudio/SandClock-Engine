#include "Cube.h"

Cube::Cube(float size, MY::Uint index) : size(size), index(index)
{}

Cube::~Cube()
{}

void Cube::Translate()
{}

void Cube::Rotate()
{}

void Cube::Draw()
{
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	/*
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, -0.5f, -4.0f); // lower left vertex
	glVertex3f(1.0f, -0.5f, -4.0f); // lower right vertex
	glVertex3f(0.0f, 0.5f, -4.0f); // upper vertex
	glEnd();
	*/
}

void Cube::Start()
{
						//1
	GLfloat vertices[] = {0,0,0,
						 size,0,0, 
						 0,size,0,
						//2
						 0,size,0,
						 size,0,0,
						 size,size,0,
						//3
						 0,size,0,
						 size,size,0,
						 0,size,size,
						//4
						 0,size,size,
						 size,size,0,
						 size,size,size,
						//5
						 size,size,0,
						 size,0,0,
						 size,0,size,
						//6
						 size,size,0,
						 size,0,size,
						 size,size,size,
						//7 
						0,size,size,
						0,0,0,
						0,size,0,
						//8
						0,size,size,
						0,0,size,
						0,0,0,
						//9
						0,0,0,
						size,0,size,
						size,0,0,
						//10
						0,0,0,
						0,0,size,
						size,0,size,
						//11
						0,size,size,
						size,size,size,
						size,0,size,
						//12
						0,size,size,
						size,0,size,
						0,0,size
						};

	glGenBuffers(1, (GLuint*) &(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_vertices * 3, vertices, GL_STATIC_DRAW);
}
