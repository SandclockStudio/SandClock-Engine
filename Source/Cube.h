#ifndef __CUBE_H__
#define __CUBE_H__

#include "Primitive.h"

#include "IL/ilut_config.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"


#pragma comment (lib, "DevIL.lib") 
#pragma comment (lib, "ILU.lib") 
#pragma comment (lib, "ILUT.lib") 
#pragma comment (lib, "assimp-vc140-mt.lib")


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

	void ImageLoad(char * imgName);
	GLuint loadImages(const char*);

private:

	MY::Uint index;
	GLfloat num_vertices = 8;
	float size;
	GLuint img;
	ILuint imgID = 0;
	GLfloat vertices[108];
};

#endif // __CUBE_H__
