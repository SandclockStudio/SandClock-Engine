#ifndef __COMPONENTMATERIAL_H_
#define __COMPONENTMATERIAL_H_

#include "Component.h"
#include "Devil\include\IL\ilut.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Globals.h"
#include <assimp/include/assimp/scene.h>



class ComponentMaterial : public Component
{
public:

	ComponentMaterial(bool start_enabled = true);
	~ComponentMaterial();

	bool Update(Frustum f);
	bool PostUpdate(Frustum f);

	void LoadMaterial(aiMaterial* material);
	void SetShader(char* name);


private:
	float ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shiness = 0.0f;
	unsigned texture = 0;

	bool shader = false;
	std::string shader_name = "test";
	bool alpha = false;

	
};

#endif // __COMPONENTMATERIAL_H_