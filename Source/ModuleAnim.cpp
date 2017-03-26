#include "ModuleAnim.h"
#include "GameObject.h"

void ModuleAnim::Load(aiString* name, aiScene* scene)
{
	
	for (int i = 0; i < scene->mNumAnimations; i++)
	{
		std::vector<myChannel> channels;
		
		for (int j = 0; j < scene->mAnimations[i][0].mNumChannels; j++)
		{
			channels.push_back(myChannel(scene->mAnimations[i][0].mChannels[j]->mNodeName, scene->mAnimations[i][0].mChannels[j]->mPositionKeys, scene->mAnimations[i][0].mChannels[j]->mRotationKeys, scene->mAnimations[i][0].mChannels[j]->mScalingKeys));
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

void ModuleAnim::Stop()
{
	for (int i = 0; i < loadAnimations.size(); i++)
	{
		loadAnimations[i].playing = false;
	}
}

update_status ModuleAnim::Update(float dt)
{
	for (int i = 0; i < loadAnimations.size(); i++)
	{
		if (loadAnimations[i].playing)
			loadAnimations[i].Update((double) dt);
	}

	return UPDATE_CONTINUE;
}

aiVector3D myAnimation::InterpolateV3(const aiVector3D previous, const aiVector3D next, float lambda)
{
	return previous * (1.0f - lambda) + next * lambda;
}

aiQuaternion myAnimation::InterpolateQuat(const aiQuaternion previous, const aiQuaternion next, float lambda)
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

	result.Normalize();

	return result;
}

void myAnimation::Update(double dt)
{
	
	GameObject* goToChange;
	aiVector3D position, scale;
	aiQuaternion rotation;
	for (int i = 0; i < channels.size(); i++)
	{
		//Cambiar FindGameObject para que no solo busque en los hijos.
		goToChange = goToChange->FindGameObject(channels[i].name);
		channels[i].currentTime += dt;

		//Interpolation
		for (int j = 0; i < channels[i].size; j++)
		{
			if (channels[i].position[j].mTime < channels[i].currentTime)
			{
				if(j != channels[i].size)
				{
					position = InterpolateV3(channels[i].position[j].mValue, channels[i].position[j + 1].mValue, channels[i].currentTime);
					scale = InterpolateV3(channels[i].scale[j].mValue, channels[i].scale[j + 1].mValue, channels[i].currentTime);
					rotation = InterpolateQuat(channels[i].rotations[j].mValue, channels[i].rotations[j + 1].mValue, channels[i].currentTime);
				}
				else
				{
					position = InterpolateV3(channels[i].position[j].mValue, channels[i].position[0].mValue, channels[i].currentTime);
					scale = InterpolateV3(channels[i].scale[j].mValue, channels[i].scale[0].mValue, channels[i].currentTime);
					rotation = InterpolateQuat(channels[i].rotations[j].mValue, channels[i].rotations[0].mValue, channels[i].currentTime);
					channels[i].currentTime = 0;
				}

				break;
			}
		}

		//Faltaria una posible rotación (?)

		goToChange->setTransformAnimation(scale, position);
	}
}
