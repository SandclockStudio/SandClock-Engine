#include "MPlane.h"

MPlane::MPlane(float size, float planeSize, MY::Uint index) : size(size), planeSize(planeSize), index(index)
{
}

MPlane::~MPlane()
{
}

void MPlane::Translate(GLfloat translation[])
{
	glTranslatef(translation[0], translation[1], translation[2]);
	glPushMatrix();
}

void MPlane::Rotate(float angle, GLfloat vector[])
{
	glRotatef(angle, vector[0], vector[1], vector[2]);
	glPushMatrix();
}

void MPlane::DrawDirect()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	for (int i = 0; i < (planeSize); i++)
	{
		for (int j = 0; j < (planeSize); j++)
		{
			if (i != 0)
			{
				glVertex3f(vertices[j + (i*(planeSize + 1))].x, vertices[j + (i*(planeSize + 1))].y, vertices[j + (i*(planeSize + 1))].z);
				glVertex3f(vertices[j + (i*(planeSize + 1))+1].x, vertices[j + (i*(planeSize + 1))+1].y, vertices[j + (i*(planeSize + 1))+1].z);
				glVertex3f(vertices[j + (i*(planeSize + 1)+ planeSize+1)].x, vertices[j + (i*(planeSize + 1) + planeSize+1)].y, vertices[j + (i*(planeSize + 1) + planeSize+1)].z);

				glVertex3f(vertices[j + (i*(planeSize + 1) + planeSize+1)].x, vertices[j + (i*(planeSize + 1) ) + planeSize+1].y, vertices[j + (i*(planeSize + 1)) + planeSize+1].z);
				glVertex3f(vertices[j + (i*(planeSize + 1)) + 1].x, vertices[j + (i*(planeSize + 1)) + 1].y, vertices[j + (i*(planeSize + 1)) + 1].z);
				glVertex3f(vertices[j + (i*(planeSize + 1) )+1+planeSize+1].x, vertices[j + (i*(planeSize + 1) )+1 + planeSize+1].y, vertices[j + (i*(planeSize + 1))+1 + planeSize+1].z);
			
			}
			else
			{
				glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
				glVertex3f(vertices[j + 1].x, vertices[j + 1].y, vertices[j + 1].z);
				glVertex3f(vertices[j + planeSize + 1].x, vertices[j + planeSize + 1].y, vertices[j + planeSize + 1].z);

				glVertex3f(vertices[j +planeSize + 1].x, vertices[j + planeSize + 1].y, vertices[j + planeSize + 1].z);
				glVertex3f(vertices[j + 1].x, vertices[j + 1].y, vertices[j + 1].z);
				glVertex3f(vertices[j + planeSize + 2].x, vertices[j +  planeSize + 2].y, vertices[j + planeSize + 2].z);
				
			}			
		}

	}
	glEnd();

}

void MPlane::Draw()
{
}

void MPlane::Start()
{
	
	for (int i = 0; i <= planeSize; i++)
	{
		for (int j = 0; j <= planeSize; j++)
		{
			if (i != 0)
			{
				vertex.Set(j*size, 0.0f, -i*size);
				vertices[j + (i*(planeSize+1))] = vertex;
			}
			else
			{
				vertex.Set(j*size, 0.0f, -i*size);
				vertices[j] = vertex;
			}

		}
	}
}
