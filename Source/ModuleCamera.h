#ifndef __MODULECAMERA_H__
#define __MODULECAMERA_H__

#include "Module.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{
	public:
		ModuleCamera();
		~ModuleCamera();
		update_status Update(float dt);
		bool Start();
		bool CleanUp();

	public:
		void SetFov();
		void SetAspectRatio();
		void SetPlaneDistances(float near, float far);
		void Position(float3 pos);
		void Orientation();
		void LookAt();
		float4x4 GetProjectionMatrix();
		float4x4 GetViewMatrix();

	private:
		Frustum f;

};

#endif // __MODULECAMERA_H__