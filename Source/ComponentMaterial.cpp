#include "ComponentMaterial.h"
#include <vector>
#include "ModuleTextures.h"
#include "Application.h"

ComponentMaterial::ComponentMaterial(bool start_enabled)
{
}

ComponentMaterial::~ComponentMaterial()
{
}

bool ComponentMaterial::Update(Frustum f)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
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

	GLfloat aux = 0;
	aiString string;
	if (material->GetTexture(aiTextureType_DIFFUSE, 0, &string, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
	{
		char* FullPath = string.data;
		aux = App->textures->loadTexture(FullPath);
		texture = aux;
	}
}


