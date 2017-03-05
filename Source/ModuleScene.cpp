#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
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
	scene = aiImportFile("Street.obj", aiProcess_TransformUVCoords | aiProcess_PreTransformVertices | aiProcess_Triangulate);

	LOGCHAR("Loading space intro");
	c = new Cube(0.5f,index);
	p = new MPlane(0.2f, 50, index);
	g = new Gizmo(0.5f, 5.0f, index);

	p->Start();
	c->Start();
	g->Start();
	batman = new Model();
	batman->Load("Batman.obj");
	
	l = new Level();
	l->Load("Street.obj");

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

GameObject * ModuleScene::CreateGameObject(aiNode * node)
{
	GameObject* myGo;

	if (node->mMeshes>0)
		myGo = new GameObject(node->mName);

	if (node->mNumChildren > 0)
	{
		for (int i = 0; i < node->mNumChildren; i++)
		{
			gameObject.push_back(myGo);
			myGo->AddChild(myGo, myGo->LoadGameObject(node->mChildren[i], scene));
		}
	}
	return myGo;
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