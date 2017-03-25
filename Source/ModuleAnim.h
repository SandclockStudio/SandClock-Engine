#ifndef __MODULE_ANIM_H_
#define __MODULE_ANIM_H_
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>



class ModuleAnim
{
public:
	void Load(aiString name,  aiString file);
	void Play();
	void Stop();
	void Draw();

public:
	

};
#endif