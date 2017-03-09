#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Cube.h"
#include "MPlane.h"
#include "Gizmo.h"
#include "Model.h"
#include "Level.h"
#include "GameObject.h"



struct SDL_Texture;

class ModuleScene : public Module
{
public:
	ModuleScene(bool active = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void LoadGameObjects(aiNode* node, GameObject* parent);

public:
	
	uint fx = 0;
	Cube* c;
	Gizmo* g;
	MPlane* p;
	MY::Uint index = 0;
	float angle = 0;
	Model* batman;
	const aiScene* scene;
	GameObject* root;

private:
	std::vector<GameObject*> gameObject;
};

#endif // __MODULESCENE_H__