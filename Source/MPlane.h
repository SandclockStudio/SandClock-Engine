#ifndef __MPLANE_H__
#define __MPLANE_H__

#include "Primitive.h"
#include "MathGeoLib.h"

class MPlane : public Primitive
{
public:

	MPlane(float size, float planeSize, MY::Uint index);

	~MPlane();

	void Translate(GLfloat translation[]);

	void Rotate(float angle, GLfloat vector[]);

	void DrawDirect();

	void Draw();

	void Start();

private:

	MY::Uint index;
	GLfloat num_vertices = 12;
	float size;
	int planeSize;
	float3 vertex;
	float3 vertices[100000];

};

#endif // __MPLANE__
