#ifndef __COMPONENTTRANSFORM_H_
#define __COMPONENTTRANSFORM_H_

#include "Component.h"
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>


class ComponentTransform : public Component
{
public:

	ComponentTransform(bool start_enabled = true);
	~ComponentTransform();

	void LoadTransform(aiNode* node);
	void Translate(aiVector3D translation);
	void Rotate(aiVector3D rotation);

private:

	aiMatrix4x4 mat;
	aiVector3D pos;
	aiQuaternion quat;
	aiVector3D scale;
};

#endif // __COMPONENTTRANSFORM_H_
