#ifndef __GIZMO_H__
#define __GIZMO_H__

#include "Primitive.h"

class Gizmo : public Primitive
{
public:

	Gizmo(float size, float width, MY::Uint index);

	~Gizmo();

	void Translate(GLfloat translation[]);

	void Rotate(float angle, GLfloat vector[]);

	void DrawDirect();

	void Draw();

	void Start();

private:

	MY::Uint index;
	GLfloat num_vertices = 6;
	float size = 0;
	float width = 0;

};

#endif // __CUBE_H__

