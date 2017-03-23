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

// Update: draw background
update_status ModuleScene::Update(float dt)
{
	gameObject[0]->Update();
	for (int i = 1; i < gameObject.size(); i++)
	{
		if (intersectFrustumAABB(componentCamera->frustum, gameObject[i]->boundingBox))
			gameObject[i]->Update();

	}
	p->DrawDirect();
	c->Draw2();


	//batman->Draw();
	//l->Draw();
	//g->DrawDirect();
	//ImGui::ShowTestWindow();


	return UPDATE_CONTINUE;
}

/**
* Tells whether or not b is intersecting f.
* @param f Viewing frustum.
* @param b An axis aligned bounding box.
* @return True if b intersects f, false otherwise.
*/
bool ModuleScene::intersectFrustumAABB(Frustum f, AABB b)
{
	// Indexed for the 'index trick' later
	float3 box[] = { b.minPoint, b.maxPoint };

	// We have 6 planes defining the frustum
	static const int NUM_PLANES = 6;
	const Plane planes[NUM_PLANES] =
	{ f.GetPlane(0), f.GetPlane(1), f.GetPlane(2), f.GetPlane(3), f.GetPlane(4), f.GetPlane(5) };

	// We only need to do 6 point-plane tests
	for (int i = 0; i < NUM_PLANES; ++i)
	{
		// This is the current plane
		const Plane p = planes[i];

		// p-vertex selection (with the index trick)
		// According to the plane normal we can know the
		// indices of the positive vertex
		const int px = static_cast<int>(p.normal.x > 0.0f);
		const int py = static_cast<int>(p.normal.y > 0.0f);
		const int pz = static_cast<int>(p.normal.z > 0.0f);

		// Dot product
		// project p-vertex on plane normal
		// (How far is p-vertex from the origin)
		const float dp =
			(p.normal.x*box[px].x) +
			(p.normal.y*box[py].y) +
			(p.normal.z*box[pz].z);

		// Doesn't intersect if it is behind the plane
		if (dp < -p.d) { return false; }
	}
	return true;
}