#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include<list>
#include "Module.h"
#include "Devil\include\IL\ilut.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	void Unload(SDL_Texture* texture);

	GLuint loadTexture(char * theFileName);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MODULETEXTURES_H__