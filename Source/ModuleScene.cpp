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
#include "ComponentTransform.h"
#include "MathGeoLib.h"

ModuleScene::ModuleScene(bool active) : Module(active)
{}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	scene = aiImportFile("Street/street.obj",  aiProcessPreset_TargetRealtime_MaxQuality);
	//scene = aiImportFile("ArmyPilot.dae", aiProcessPreset_TargetRealtime_MaxQuality);

	LOGCHAR("Loading space intro");
	c = new Cube(0.5f,index);
	p = new MPlane(0.2f, 50, index);
	g = new Gizmo(0.5f, 5.0f, index);

	p->Start();
	c->Start();
	g->Start();
	batman = new Model();
	batman->Load("Batman.obj");
	camera = new GameObject((aiString)"Camera", nullptr);
	componentCamera = new ComponentCamera();
	camera->AddComponent(componentCamera);
	gameObject.push_back(camera);
	root = new GameObject(scene->mRootNode->mName,nullptr);
	ComponentTransform rootTransform;
	rootTransform = new ComponentTransform();
	rootTransform.LoadTransform(scene->mRootNode);
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
	for (int i = 0; i < gameObject.size();++i)
	{
		gameObject[i]->CleanUp();
		RELEASE(gameObject[i]);
	}

	return true;
}

void  ModuleScene::LoadGameObjects(aiNode * node,GameObject* parent)
{
	GameObject* object = new GameObject(node->mName, parent);

	if (node->mNumMeshes > 1)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			GameObject* my_go = object->LoadGameObjectMesh(node, scene->mMeshes[i], scene);
			parent->AddChild(my_go, parent);
			my_go->SetRootNode(parent);
			gameObject.push_back(my_go);
		}
	}
	else if (node->mNumMeshes == 1)
	{
		GameObject* my_go = object->LoadGameObjectMesh(node, scene->mMeshes[node->mMeshes[0]], scene);
		parent->AddChild(my_go, parent);
		my_go->SetRootNode(parent);
		gameObject.push_back(my_go);
	}
	else
	{
		GameObject* my_go = object->LoadGameObject(node,scene);
		parent->AddChild(object, parent);
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		if(parent->GetRootNode() != nullptr)
			object->SetRootNode(parent);

		LoadGameObjects(node->mChildren[i], object);
	}
}

update_status ModuleScene::PreUpdate(float dt)
{

	for (int i = 0; i < gameObject.size(); i++)
	{
		
			gameObject[i]->PreUpdate();
	}

	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update(float dt)
{


	gameObject[0]->Update(componentCamera->frustum);

	std::vector<GameObject*> childs = root->getChilds();


	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Update(componentCamera->frustum);

		glPushMatrix();
		childs[i]->DrawBoundingBox();
		glPopMatrix();
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
/*
// Update: draw background
update_status ModuleScene::Update(float dt)
{
	gameObject[0]->Update(componentCamera->frustum);
	for (int i = 1; i < gameObject.size(); i++)
	{
		if (gameObject[i]->intersectFrustumAABB(componentCamera->frustum, gameObject[i]->boundingBox))
			gameObject[i]->Update(componentCamera->frustum);

	}
	p->DrawDirect();
	c->Draw2();


	//batman->Draw();
	//l->Draw();
	//g->DrawDirect();
	//ImGui::ShowTestWindow();


	return UPDATE_CONTINUE;
}*/

