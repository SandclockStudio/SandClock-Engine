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

	GameObject* CreateGameObject(aiNode* node);

public:
	
	uint fx = 0;
	Cube* c;
	Gizmo* g;
	MPlane* p;
	Level* l;
	Level* l2;
	MY::Uint index = 0;
	float angle = 0;
	Model* batman;
	const aiScene* scene;

private:
	std::vector<GameObject*> gameObject;
};

#endif // __MODULESCENE_H__