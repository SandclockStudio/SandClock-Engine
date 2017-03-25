#include "ModuleAnim.h"


void ModuleAnim::Load(aiString* name, aiScene* scene)
{
	
	for (int i = 0; i < scene->mNumAnimations; i++)
	{
		std::vector<myChannel> channels;
		for (int j = 0; j < scene->mAnimations[i][0].mNumChannels; j++)
		{
			channels.push_back(myChannel(scene->mAnimations[i][0].mChannels[j]->mNodeName, scene->mAnimations[i][0].mChannels[j]->mPositionKeys, scene->mAnimations[i][0].mChannels[j]->mRotationKeys));
		}

		myAnimation aux = myAnimation(i, channels,scene->mAnimations[i][0].mDuration);
		loadAnimations.push_back(aux);
	}
}

void ModuleAnim::Play()
{
}

void ModuleAnim::Stop()
{
}

void ModuleAnim::Draw()
{
}
