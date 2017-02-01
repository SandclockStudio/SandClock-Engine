#ifndef __CUBE_H__
#define __CUBE_H__

#include "Primitive.h"

class Cube : public Primitive
{
public:

	Cube();

	~Cube();

	void Translate();

	void Rotate();

	void Draw();
};

#endif // __CUBE_H__
