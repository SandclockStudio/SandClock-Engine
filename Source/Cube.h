#ifndef __CUBE_H__
#define __CUBE_H__

#include "Primitive.h"

class Cube : public Primitive
{
public:

	Cube(float size, MY::Uint index);

	~Cube();

	void Translate(GLfloat translation[]);

	void Rotate(float angle, GLfloat vector[]);

	void DrawDirect();

	void Draw();

	void Draw2();

	void Start();

private:

	MY::Uint index;
	GLfloat num_vertices = 8;
	float size;
	GLuint lenaImg;

};

#endif // __CUBE_H__
