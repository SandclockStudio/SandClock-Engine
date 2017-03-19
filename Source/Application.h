#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "SimpleTimer.h"
#include "Timer.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleParticles;
class ModuleUI;
class ModuleEditor;

//JSON Parser
class JsonParser;


// Game modules ---
class ModulePlayer;
class ModuleEnemy;
class ModuleScene;
class ModuleSceneLevel;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;
	ModuleParticles* particles;
	ModuleEditor* editor;

	JsonParser* json_parser;
	SimpleTimer mili;
	Timer micro,dtTimer;
	float dt = 0;
	int fps = 0;

	// Game modules --
	ModuleUI* ui;
	ModulePlayer* player;
	ModuleScene* scene_intro;
	ModuleEnemy* enemies;


private:

	bool start = true;
	int frames = 0;
	char newTitle[30];
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__