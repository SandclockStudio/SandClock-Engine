#include "Gizmo.h"

Gizmo::Gizmo(float size, float width, MY::Uint index) : size(size), width(width), index(index)
{}

Gizmo::~Gizmo()
{}

void Gizmo::Translate(GLfloat translation[])
{
	glTranslatef(translation[0], translation[1], translation[2]);
	glPushMatrix();

}

void Gizmo::Rotate(float angle, GLfloat vector[])
{
	glRotatef(angle, vector[0], vector[1], vector[2]);
	glPushMatrix();
}

void Gizmo::DrawDirect()
{
	glLineWidth(width);

	glBegin(GL_LINES);

	glDepthRange(0.0, 0.1);
	//X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(size, 0.0f, 0.0f);
	//Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, size, 0.0f);
	//Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, size);
	glEnd();

	glLineWidth(1.0f);
}

void Gizmo::Draw()
{

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawArrays(GL_LINES, 0, num_vertices * 2);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void Gizmo::Start()
{
	//1
	GLfloat vertices[] = { 0,0,0,
		size,0,0,
		//2
		0,0,0,
		0,size,0,
		//3
		0,0,0,
		0,0,size
	};


	glGenBuffers(1, (GLuint*)&(index));
	glBindBuffer(GL_ARRAY_BUFFER, index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*num_vertices * 3, vertices, GL_STATIC_DRAW);

}