#ifndef __BILLBOARD_H
#define __BILLBOARD_H

#include "IL/ilut_config.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"


#pragma comment (lib, "DevIL.lib") 
#pragma comment (lib, "ILU.lib") 
#pragma comment (lib, "ILUT.lib") 
#pragma comment (lib, "assimp-vc140-mt.lib")


class Billboard
{
public:

	Billboard();
	~Billboard();

	bool Init();
	bool Draw();
	bool Update();

private:
	GLuint loadImages(const char*);

private:

	unsigned int texture;
	float size;
};

#endif
