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

	bool PreUpdate();
	bool Update();

	void LookAt(float xRotation, float yRotation);
	void Position(float3 pos);
	void SetFov(float newFOV);
	void SetAspectRatio(float newAspectRatio);
	void SetPlaneDistances(float near, float);
	float * GetProjectionMatrix();
	float * GetViewMatrix();

private:

	float4x4 matrix;
	Quat quaternion;
	Frustum frustum;
	float speed, rotation_speed;
	float3 movement;
	float dt;
	
};

#endif // __COMPONENTTRANSFORM_H_

