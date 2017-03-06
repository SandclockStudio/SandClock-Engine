#include "ComponentMaterial.h"
#include <vector>


ComponentMaterial::ComponentMaterial(bool start_enabled)
{
}

ComponentMaterial::~ComponentMaterial()
{
}

bool ComponentMaterial::Update()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);

	return true;
}

void ComponentMaterial::LoadMaterial(aiMaterial * material)
{

	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	material->Get(AI_MATKEY_COLOR_SPECULAR, specular);

	if (material->Get(AI_MATKEY_SHININESS, shiness) == AI_SUCCESS)
		shiness *= 128.0f;

	float shine_strength = 1.0f;

	if (material->Get(AI_MATKEY_SHININESS_STRENGTH, shine_strength) == AI_SUCCESS)
	{
		specular[0] *= shine_strength;
		specular[1] *= shine_strength;
		specular[2] *= shine_strength;
		specular[3] *= shine_strength;

	}
		

	for (int i = 0; i < 3; i++)
	{
		ambient[i] = ambient[i];
		diffuse[i] = diffuse[i];
		specular[i] = specular[i];
	}
}


