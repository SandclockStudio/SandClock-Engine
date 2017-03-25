#ifndef __MODULE_ANIM_H_
#define __MODULE_ANIM_H_

#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>
#include "Module.h"
#include <vector>


struct myChannel
{
	myChannel(aiString name, aiVectorKey*, aiQuatKey*)
	{};
	aiVectorKey* position;
	aiQuatKey* rotations;
	aiString name;
};


struct myAnimation
{
	myAnimation(float, std::vector<myChannel>,double)
	{};
	float id;
	std::vector<myChannel> channels;
	double duration;
};

class ModuleAnim:Module
{
public:

	void Load(aiString * name, aiScene * scene);
	void Play();
	void Stop();
	void Draw();

public:

	std::vector<myAnimation> loadAnimations;

};
#endif
