#ifndef __MODULE_ANIM_H_
#define __MODULE_ANIM_H_

#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>
#include "Module.h"
#include <vector>
#include <map>



struct myChannel
{
	myChannel(aiString name, aiVectorKey* position, aiQuatKey* rotations,aiVectorKey* scale,float size) : name(name), position(position), rotations(rotations), scale(scale),size(size)
	{
	};

	aiVectorKey* position;
	aiQuatKey* rotations;
	aiVectorKey* scale;
	aiString name;
	unsigned int size;
	float currentTime = 0;
};


struct myAnimation
{
	myAnimation(float id, std::vector<myChannel> channels,double duration) : id(id), channels(channels), duration(duration)
	{};

	aiVector3D InterpolateV3(const aiVector3D previous, const aiVector3D next, float lambda);
	aiQuaternion InterpolateQuat(const aiQuaternion & previous, const aiQuaternion & next, float lambda);

	void Update(float dt);
	bool playing = false;
	float id;
	std::vector<myChannel> channels;
	double duration;
};

class ModuleAnim : public Module
{
public:
	void Load(const char * name);
	void PlayAnimation(float index);
	void PlayAll();
	void Stop();
	update_status Update(float dt);

public:

	std::vector<myAnimation> loadAnimations;

};
#endif
