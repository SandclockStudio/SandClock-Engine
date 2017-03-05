#ifndef __COMPONENTMATERIAL_H_
#define __COMPONENTMATERIAL_H_

#include "Component.h"



class ComponentMaterial : public Component
{
public:

	ComponentMaterial(bool start_enabled = true);
	~ComponentMaterial();


	bool Update();

	void LoadMaterial(aiMaterial* material);

	GLuint loadTexture(char * theFileName);

private:
	float ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shiness = 0.0f;

	public:
	unsigned texture = 0;

	
};

#endif // __COMPONENTMATERIAL_H_