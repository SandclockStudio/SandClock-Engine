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
}

void Cube::Start()
{

	GLfloat vertices[] = { 0,0,0 };
	glGenBuffers(1, (GLuint*) &(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_vertices * 3, vertices, GL_STATIC_DRAW);
}
