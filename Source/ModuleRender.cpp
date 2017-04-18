#include "../Libraries/OpenGL/include/GL/glew.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "JsonParser.h"
#include "MathGeoLib.h" #pragma comment (lib, "MathGeoLib.lib")

#include "IMGUI/imgui.h"

#include "ModuleEditor.h"
#include "ModuleScene.h"

#pragma comment (lib, "opengl32.lib") 

ModuleRender::ModuleRender()
{
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	fpsDependent = true;
	if (App->json_parser->LoadObject("Config.App"))
	{
		fps_cap = App->json_parser->GetInt("fps_cap");
		App->json_parser->UnloadObject();
	}
	LOGCHAR("Creating Renderer context");
	App->editor->AddLog("Creating Renderer context \n");
	bool ret = true;
	Uint32 flags = 0;

	if (LoadConfig() == false)
	{
		LOGCHAR("Problem in the configuration file");
		App->editor->AddLog("Problem in the configuration file\n");
		ret = false;
	}

	if(vsync == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	flags |= SDL_WINDOW_OPENGL;

	context = SDL_GL_CreateContext(App->window->window);

	if (context == nullptr)
	{
		LOGCHAR("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		App->editor->AddLog("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		LOGCHAR("Glew library could not init %s\n", glewGetErrorString(err));
		ret = false;
	}

	LOGCHAR("Using Glew %s", glewGetString(GLEW_VERSION));
	App->editor->AddLog("Using Glew %s", glewGetString(GLEW_VERSION));
	LOGCHAR("Vendor %s", glGetString(GL_VENDOR));
	App->editor->AddLog("Vendor %s", glGetString(GL_VENDOR));
	LOGCHAR("Renderer %s", glGetString(GL_RENDERER));
	App->editor->AddLog("Renderer %s", glGetString(GL_RENDERER));
	LOGCHAR("OpenGL version supported %s", glGetString(GL_VERSION));
	App->editor->AddLog("OpenGL version supported %s", glGetString(GL_VERSION));
	LOGCHAR("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	App->editor->AddLog("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));


	renderer = SDL_CreateRenderer(App->window->window, -1, 0);
	
	if(renderer == nullptr)
	{
		LOGCHAR("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		//GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//GLfloat light_position[] = { 0.25f, 1.0f, 1.0f, 0.0 };
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glFrontFace(GL_CCW), glCullFace(GL_BACK);
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	

	return ret;
}

update_status ModuleRender::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(float dt)
{
	
	ImGui::Render();
	
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOGCHAR("Destroying renderer");
	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

bool ModuleRender::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		screenWidth = App->json_parser->GetInt("Width");
		screenHeight = App->json_parser->GetInt("Height");
		screenSize = App->json_parser->GetInt("Size");
		vsync = App->json_parser->GetBool("Vsync");
		return_value = App->json_parser->UnloadObject();
	}

	return return_value;
}