#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__
#include "../Libraries/OpenGL/include/GL/glew.h"
#include "Globals.h"
#pragma comment (lib, "opengl32.lib") 

class Primitive
{
public:

	Primitive()
	{}

	virtual ~Primitive()
	{}

	virtual void Translate()
	{}

	virtual void Rotate()
	{}

	virtual void Draw()
	{}

	virtual void DrawDirect()
	{}

	virtual void Start()
	{}

	GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],GLfloat fVert3[], 
		GLfloat *fNormalX,GLfloat *fNormalY, GLfloat *fNormalZ)
	{
		GLfloat Qx, Qy, Qz, Px, Py, Pz;

		Qx = fVert2[0] - fVert1[0];
		Qy = fVert2[1] - fVert1[1];
		Qz = fVert2[2] - fVert1[2];
		Px = fVert3[0] - fVert1[0];
		Py = fVert3[1] - fVert1[1];
		Pz = fVert3[2] - fVert1[2];

		*fNormalX = Py*Qz - Pz*Qy;
		*fNormalY = Pz*Qx - Px*Qz;
		*fNormalZ = Px*Qy - Py*Qx;

	}
};

#endif // __PRIMITIVE_H__

