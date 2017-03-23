#ifndef __COMPONENTCAMERA_H_
#define ____COMPONENTCAMERA_H__H_

#include "Component.h"
#include <vector>
#include "MathGeoLib.h"


class ComponentCamera : public Component
{
public:

	ComponentCamera(bool start_enabled = true);
	~ComponentCamera();

	bool PreUpdate();
	bool Update();

	void LookAt(float dx, float dy);
	void Position(float3 pos);
	void SetFov(float newFOV);
	void SetAspectRatio(float newAspectRatio);
	void SetPlaneDistances(float, float);
	float * GetProjectionMatrix();
	float * GetViewMatrix();
	Frustum frustum;

private:

	float4x4 matrix;
	Quat quaternion;

	float speed, rotation_speed;
	float3 movement;
	float dt;
	
};

#endif // ____COMPONENTCAMERA_H_

