#include "ModuleAnim.h"
#include "Application.h"
#include  "ModuleScene.h"
#include "ComponentTransform.h"
#include "GameObject.h"

void ModuleAnim::Load(const char* name)
{
	gameModule = true;
	const aiScene* scene = aiImportFile(name, aiProcessPreset_TargetRealtime_MaxQuality);
	
	for (int i = 0; i < scene->mNumAnimations; i++)
	{
		std::vector<myChannel> channels;
		
		for (int j = 0; j < scene->mAnimations[i][0].mNumChannels; j++)
		{
			channels.push_back(myChannel(scene->mAnimations[i][0].mChannels[j]->mNodeName, scene->mAnimations[i][0].mChannels[j]->mPositionKeys, scene->mAnimations[i][0].mChannels[j]->mRotationKeys, scene->mAnimations[i][0].mChannels[j]->mScalingKeys, scene->mAnimations[i][0].mChannels[j]->mNumPositionKeys));
		}

		myAnimation aux = myAnimation(i, channels,scene->mAnimations[i][0].mDuration);
		loadAnimations.push_back(aux);
	}
}

void ModuleAnim::PlayAnimation(float index)
{
		loadAnimations[index].playing = true;
}

void ModuleAnim::PlayAll()
{
	for (int i = 0; i < loadAnimations.size(); i++)
	{
		loadAnimations[i].playing = true;
	}
}
/*
void ModuleAnim::Stop()
{
	for (int i = 0; i < loadAnimations.size(); i++)
	{
		loadAnimations[i].playing = false;
	}
}*/

update_status ModuleAnim::Update(float dt)
{
	if(dt != 0)
		for (int i = 0; i < loadAnimations.size(); i++)
		{
			if (loadAnimations[i].playing)
				loadAnimations[i].Update(dt);
		}

	return UPDATE_CONTINUE;
}

aiVector3D myAnimation::InterpolateV3(const aiVector3D previous, const aiVector3D next, float lambda)
{
	return previous * (1.0f - lambda) + next * lambda;
}

aiQuaternion myAnimation::InterpolateQuat(const aiQuaternion& previous, const aiQuaternion& next, float lambda)
{
	aiQuaternion result;
	float dot = previous.x * next.x + previous.y * next.y + previous.z * next.z + previous.w * next.w;

	if (dot >= 0.0f)
	{
		result.x = previous.x * (1.0f - lambda) + next.x * lambda;
		result.y = previous.y * (1.0f - lambda) + next.y * lambda;
		result.z = previous.z * (1.0f - lambda) + next.z * lambda;
		result.w = previous.w * (1.0f - lambda) + next.w * lambda;
	}
	else
	{
		result.x = previous.x * (1.0f - lambda) + next.x * -lambda;
		result.y = previous.y * (1.0f - lambda) + next.y * -lambda;
		result.z = previous.z * (1.0f - lambda) + next.z * -lambda;
		result.w = previous.w * (1.0f - lambda) + next.w * -lambda;
	}

	result.Normalize();

	return result;
}

void myAnimation::Update(float dt)
{
	GameObject* goToChange = nullptr;
	aiVector3D position, scale;
	aiQuaternion rotation;

	for (int i = 0; i < channels.size(); i++)
	{
		//Buscar el gameObject con el nombre que toca
		for (int k = 0; k < App->scene_intro->gameObject.size();k++)
		{
			if (channels[i].name == App->scene_intro->gameObject[k]->GetName())
			{
				goToChange = App->scene_intro->gameObject[k];
				break;
			}
		}

		//Si no se ha devuelto ninguno no se hace nada
		if (goToChange != nullptr)
		{
			channels[i].currentTime += App->timeScale*dt;

			//Interpolation
			for (int j = 0; j < channels[i].size; j++)
			{
				//Si estas en la ultima iteración se pone el tiempo de la animación a cero.
				if (j + 1 == channels[i].size)
				{
					channels[i].currentTime = 0;
					break;
				}

				//Si el tiempo actual es mayor que el de la iteración y menor que el siguiente se calcula
				if (channels[i].position[j].mTime < channels[i].currentTime && channels[i].position[j + 1].mTime > channels[i].currentTime)
				{
					float pos_key = float(channels[i].currentTime * (channels[i].size - 1)) / float(duration);
					float rot_key = float(channels[i].currentTime * (channels[i].size - 1)) / float(duration);

					float pos_lambda = pos_key - j;
					float rot_lambda = rot_key - j;

					unsigned int pos_index = unsigned(pos_key);
					unsigned int rot_index = unsigned(rot_key);
					unsigned int pos_index_sec = (pos_index + 1) % channels[i].size;
					unsigned int rot_index_sec = (rot_index + 1) % channels[i].size;
					

					position = InterpolateV3(channels[i].position[pos_index].mValue, channels[i].position[pos_index_sec].mValue, pos_lambda);
					rotation = InterpolateQuat(channels[i].rotations[pos_index].mValue, channels[i].rotations[pos_index_sec].mValue, rot_lambda);
					scale = InterpolateV3(channels[i].scale[j].mValue, channels[i].scale[j + 1].mValue, 1);

					Quat rotationQuat = Quat(rotation.x, rotation.y, rotation.z, rotation.w);
					goToChange->setTransformAnimation(scale, position, rotationQuat);
					goToChange = nullptr;
					break;
				}
			}
		}
	}
}
