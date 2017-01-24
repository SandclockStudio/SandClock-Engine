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

//JSON Parser
class JsonParser;


// Game modules ---
class ModulePlayer;
class ModuleEnemy;
class ModuleSceneIntro;
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

	JsonParser* json_parser;
	SimpleTimer mili;
	Timer micro;


	// Game modules --
	ModuleUI* ui;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleSceneLevel* scene_level;
	ModuleEnemy* enemies;


private:

	bool start = true;
	int fps = 0;
	int frames = 0;

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__