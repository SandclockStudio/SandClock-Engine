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
		void SetPlaneDistances();
		void Position();
		void Orientation();
		void LookAt();
		void GetProjectionMatrix();
		void GetViewMatrix();
		
		GLfloat projectionMatrix [16];
		GLfloat viewMatrix[16];

	private:
		Frustum f;

};

#endif // __MODULECAMERA_H__