#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
//#include "Cube.h"
//#include "MPlane.h"
//#include "Gizmo.h"
#include "Model.h"
#include "Level.h"
#include "ComponentCamera.h"
#include "QuadTreeNode.h"
#include "GrassBillboard.h"
#include "ComponentTransform.h"
#include "ComponentRigidbody.h"
#include "ComponentMesh.h"


struct SDL_Texture;

class ModuleScene : public Module
{
public:
	ModuleScene(bool active = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadGameObjects(aiNode * node, GameObject * parent, const aiScene * myscene);



	update_status PreUpdate(float dt);

public:
	
	uint fx = 0;
	//Cube* c;
	//Gizmo* g;
	//MPlane* p;
	MY::Uint index = 0;
	float angle = 0;
	Model* batman;
	const aiScene* scene;
	const aiScene* scene2;
	GameObject* root;
	GameObject* root2;
	GameObject* camera;
	ComponentCamera* componentCamera;
	ComponentTransform* rootTransform;
	ComponentTransform* rootTransform2;

	float positionXcamera, positionYCamera,positionZcamera, rotationX, rotationY;

	QuadTreeNode* quadTree;
	GameObject* aaaa;
	std::vector<GameObject*> gameObject;

	GrassBillboard * billboard;

	GameObject* physicObject;
	ComponentRigidbody* rigidBody;
	ComponentTransform* transform;
	ComponentMesh* mesh;

private:
	GameObject * object;
	GameObject * my_go;

	
};

#endif // __MODULESCENE_H__