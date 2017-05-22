#include "DebugDrawer.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


void DebugDrawer::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	glPushMatrix();

//	glColor3f(color.x, color.y, color.z);

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glVertex3fv((GLfloat*)&from);
	glVertex3fv((GLfloat*)&to);

	glEnd();

	glPopMatrix();
}
