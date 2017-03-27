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
#include "ModuleAnim.h"
#include "Application.h"

ModuleScene::ModuleScene(bool active) : Module(active)
{}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	scene = aiImportFile("ArmyPilot.dae",  aiProcessPreset_TargetRealtime_MaxQuality);
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
	ComponentTransform* rootTransform;
	rootTransform = new ComponentTransform();
	App->animations->Load("ArmyPilot_Run_Forwards.fbx");
	App->animations->PlayAll();
	rootTransform->LoadTransform(scene->mRootNode);
	root->AddComponent(rootTransform);
	LoadGameObjects(scene->mRootNode, root);

	quadTree = new QuadTreeNode();
	quadTree->Create(AABB(float3(-10, 1, -10), float3(10, 1, 10)));
	
	GameObject * aaaa = new GameObject(aiString("AAAA"));
	aaaa->boundingBox = AABB(float3(-8, 1, -8), float3(-6, 1, -6));

	GameObject * bbbb = new GameObject(aiString("BBBB"));
	bbbb->boundingBox = AABB(float3(-6, 1, -6), float3(-4, 1, -4));

	GameObject * cccc = new GameObject(aiString("CCCC"));
	cccc->boundingBox = AABB(float3(8, 1, 8), float3(6, 1, 6));

	GameObject * dddd = new GameObject(aiString("DDDD"));
	dddd->boundingBox = AABB(float3(6, 1, 6), float3(4, 1, 4));

	GameObject * eeee = new GameObject(aiString("EEEE"));
	eeee->boundingBox = AABB(float3(-8, 1, 8), float3(-6, 1, 6));

	
	quadTree->Insert(aaaa);
	quadTree->Insert(bbbb);
	quadTree->Insert(cccc);
	quadTree->Insert(dddd);
	//quadTree->Insert(eeee);
	
	/*for (int i = 0; i < root->getChilds().size(); i++) 
	{
		
		quadTree->Insert(root->getChilds()[i]);
	}*/

	

	return true;
}

/*vector<GameObject*> ModuleScene::CreateTestGameObjects()
{

	GameObject* object = new GameObject(, parent);
}*/

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
	delete(quadTree);

	return true;
}

void  ModuleScene::LoadGameObjects(aiNode * node,GameObject* parent)
{
	GameObject* object = new GameObject(node->mName, parent);
	GameObject* my_go;
	if (node->mNumMeshes > 1)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			my_go = object->LoadGameObjectMesh(node, scene->mMeshes[i], scene);
			parent->AddChild(my_go);
			my_go->SetRootNode(parent);
			gameObject.push_back(my_go);
		}
	}
	else if (node->mNumMeshes == 1)
	{
		 my_go = object->LoadGameObjectMesh(node, scene->mMeshes[node->mMeshes[0]], scene);
		parent->AddChild(my_go);
		my_go->SetRootNode(parent);
		gameObject.push_back(my_go);
	}
	else
	{
		my_go = object->LoadGameObject(node);
		parent->AddChild(my_go);
		gameObject.push_back(my_go);
		my_go->SetRootNode(parent);

	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		if(parent->GetRootNode() != nullptr)
			object->SetRootNode(parent);

		LoadGameObjects(node->mChildren[i], my_go);
	}
}

update_status ModuleScene::PreUpdate(float dt)
{

	std::vector<GameObject*> childs = root->getChilds();

	for (int i = 0; i < childs.size(); i++)
	{
		
		childs[i]->PreUpdate();
	}
	gameObject[0]->PreUpdate();

	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt)
{
	gameObject[0]->Update(componentCamera->frustum);

	std::vector<GameObject*> childs = root->getChilds();

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Update(componentCamera->frustum);
		childs[i]->DrawLines();


		glPushMatrix();
		childs[i]->DrawBoundingBox();
		glPopMatrix();
	}
	p->DrawDirect();
	c->Draw2();

	//quadTree->root->DebugDraw();

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

