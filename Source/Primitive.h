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

	virtual void Start()
	{}
};

#endif // __PRIMITIVE_H__

