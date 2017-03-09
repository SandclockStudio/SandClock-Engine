#ifndef __COMPONENTTRANSFORM_H_
#define __COMPONENTTRANSFORM_H_

#include "Component.h"
#include <vector>
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>
#include "MathGeoLib.h"


class ComponentCamera : public Component
{
public:

	ComponentCamera(bool start_enabled = true);
	~ComponentCamera();

	void LoadCamera(aiNode* node);
	void Translate(aiVector3D translation);
	void Rotate(aiVector3D rotation);
	bool Update();

private:

	aiMatrix4x4 mat;
	aiVector3D pos;
	aiQuaternion quat;
	aiVector3D scale;

	Frustum frustum;
	float speed, rotation_speed, xRotation, yRotation;
	float3 movement;
	
};

#endif // __COMPONENTTRANSFORM_H_

