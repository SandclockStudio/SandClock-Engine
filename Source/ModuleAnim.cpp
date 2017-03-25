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
		loadAnimations[i].currentTime = 0;
	}
}

update_status ModuleAnim::Update(float dt)
{
	for (int i = 0; i < loadAnimations.size(); i++)
	{
		if (loadAnimations[i].playing)
			loadAnimations[i].Update((double) dt);
	}
}

aiVector3D ModuleAnim::InterpolateV3(const aiVector3D previous, const aiVector3D next, float lambda) 
{
	return previous * (1.0f - lambda) + next * lambda;
}

aiQuaternion ModuleAnim::InterpolateQuat(const aiQuaternion previous, const aiQuaternion next, float lambda)
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
	currentTime += dt;
	GameObject* goToChange;
	for (int i = 0; i < channels.size(); i++)
	{
		//Cambiar FindGameObject para que no solo busque en los hijos.
		goToChange = goToChange->FindGameObject(channels[i].name);
		//Crear metodo que devuelva el componentTransform del gameObject encontrado.
		for (int j = 0; i < sizeof(channels[i].position); j++)
		{
			
		}

	}
}
