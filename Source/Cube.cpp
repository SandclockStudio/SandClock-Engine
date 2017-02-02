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
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	//front
	glColor3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(size, 0.0f, 0.0f); 
	glVertex3f(0.0f, size, 0.0f); 

	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size, size, 0.0f); 

	

	//up
	glColor3f(0, 1, 0);
	glVertex3f(0.0f, size, 0.0f);
	glVertex3f(size, size, 0.0f);
	glVertex3f(0.0f, size, -size);

	glVertex3f(0.0f, size, -size); 
	glVertex3f(size, size, 0.0f);
	glVertex3f(size, size, -size); 

	//right
	glColor3f(0, 0, 1);
	glVertex3f(size, size, 0); 
	glVertex3f(size, 0.0f, 0.0f); 
	glVertex3f(size, 0.0f, -size); 

	glVertex3f(size, size, 0.0f); 
	glVertex3f(size, 0.0f, -size); 
	glVertex3f(size, size, -size); 
	//left
	glColor3f(0, 1, 1);
	glVertex3f(0.0f, size, -size); 
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, size, 0.0f); 

	glVertex3f(0.0f, size, -size); 
	glVertex3f(0.0f, 0.0f,-size); 
	glVertex3f(0.0f, 0.0f, 0.0f); 

	//Down
	glColor3f(0.5f, 1, 1);
	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(size, 0.0f, -size); 
	glVertex3f(size, 0.0f, 0.0f); 

	glVertex3f(0.0f, 0.0f, 0.0f); 
	glVertex3f(0.0f, 0.0f, -size); 
	glVertex3f(size, 0.0f, -size); 

	//back
	glColor3f(0.5f, 0.5f, 1);
	glVertex3f(0.0f, size, -size); 
	glVertex3f(size, size, -size); 
	glVertex3f(size, 0.0f, -size); 

	glVertex3f(0.0f, size, -size); 
	glVertex3f(size, 0.0f, -size); 
	glVertex3f(0.0f, 0.0f, -size); 
	glEnd();
}

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
						 0,size,-size,
						//4
						 0,size,-size,
						 size,size,0,
						 size,size,-size,
						//5
						 size,size,0,
						 size,0,0,
						 size,0,-size,
						//6
						 size,size,0,
						 size,0,-size,
						 size,size,-size,
						//7 
						0,size,-size,
						0,0,0,
						0,size,0,
						//8
						0,size,-size,
						0,0,-size,
						0,0,0,
						//9
						0,0,0,
						size,0,-size,
						size,0,0,
						//10
						0,0,0,
						0,0,-size,
						size,0,-size,
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
