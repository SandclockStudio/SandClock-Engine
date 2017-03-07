#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene.h"
#include "assimp\include\assimp\scene.h"
#include "IMGUI\imgui.h"
#include "Level.h"
#include "assimp\include\assimp\cimport.h"
#include <assimp\include\assimp\postprocess.h>
#include "Component.h"
ModuleScene::ModuleScene(bool active) : Module(active)
{}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	scene = aiImportFile("ArmyPilot.dae",  aiProcessPreset_TargetRealtime_MaxQuality);

	LOGCHAR("Loading space intro");
	c = new Cube(0.5f,index);
	p = new MPlane(0.2f, 50, index);
	g = new Gizmo(0.5f, 5.0f, index);

	p->Start();
	c->Start();
	g->Start();
	batman = new Model();
	batman->Load("Batman.obj");
	root = new GameObject(scene->mRootNode->mName,nullptr);
	l = new Level();
	l->Load("street/Street.obj");

	LoadGameObjects(scene->mRootNode, root);

	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOGCHAR("Unloading space scene");
	delete(c);
	delete(p);
	delete(g);
	//batman->Clear();
	return true;
}

void  ModuleScene::LoadGameObjects(aiNode * node,GameObject* parent)
{
	GameObject* object = new GameObject(node->mName,parent);


	if (node->mNumMeshes > 1)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			GameObject* meshObject = GameObject::LoadGameObjectMesh(node,scene->mMeshes[i],scene);
			gameObject.push_back(meshObject);
		}
	}
	else if (node->mNumMeshes == 1)
	{
		GameObject* newGameObject = GameObject::LoadGameObjectMesh(node, scene->mMeshes[node->mMeshes[0]], scene);
		gameObject.push_back(newGameObject);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		GameObject* child = GameObject::LoadGameObject(node->mChildren[i], scene);
		LoadGameObjects(node->mChildren[i], object);
		parent->AddChild(child, parent);
		child->SetRootNode(parent);
		gameObject.push_back(child);
	}
}

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	std::vector<Component*>::iterator it;
	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i]->Update();
	}

	p->DrawDirect();
	c->Draw2();
	//batman->Draw();
	//l->Draw();
	//g->DrawDirect();
	//ImGui::ShowTestWindow();

	/*

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_level, this);
		App->audio->PlayFx(fx);
	}
	*/

	return UPDATE_CONTINUE;
}