#ifndef __MODULECAMERA_H__
#define __MODULECAMERA_H__

#include "Module.h"
#include "MathGeoLib.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 

class ModuleCamera : public Module
{
	public:
		ModuleCamera();
		~ModuleCamera();
		bool Init();
		update_status Update(float dt);
		bool Start();
		bool CleanUp();

	public:
		void SetPlaneDistances(float near, float far);
		void Position(float3 pos);
		void SetFov(float newFOV);
		void SetAspectRatio(float newAspectRatio);
		void Orientation();
		void LookAt(float3, float3);
		float* GetProjectionMatrix();
		float* GetViewMatrix();
		bool LoadConfig();


	private:
		Frustum f;
		float speed;
		float3 right;
		float3 forward;
		float3 movement;
};

#endif // __MODULECAMERA_H__