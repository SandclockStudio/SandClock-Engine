#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "JsonParser.h"
#include "MathGeoLib.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = screenWidth * screenSize;
	camera.h = screenHeight* screenSize;
	fpsDependent = true;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOGCHAR("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (LoadConfig() == false)
	{
		LOGCHAR("Problem in the configuration file");
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
		ret = false;
	}

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		LOGCHAR("Glew library could not init %s\n", glewGetErrorString(err));
		ret = false;
	}

	LOGCHAR("Using Glew %s", glewGetString(GLEW_VERSION));
	LOGCHAR("Vendor %s", glGetString(GL_VENDOR));
	LOGCHAR("Renderer %s", glGetString(GL_RENDERER));
	LOGCHAR("OpenGL version supported %s", glGetString(GL_VERSION));
	LOGCHAR("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));


	renderer = SDL_CreateRenderer(App->window->window, -1, 0);
	
	if(renderer == nullptr)
	{
		LOGCHAR("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}


	return ret;
}

update_status ModuleRender::PreUpdate(float dt)
{
	glViewport(0, 0, screenWidth*screenSize, screenHeight*screenSize);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glFrustum(-1.0,1.0f,-1.0f,1.0f,2.0f,5.0f);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update(float dt)
{

	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, -0.5f, -4.0f); // lower left vertex
	glVertex3f(1.0f, -0.5f, -4.0f); // lower right vertex
	glVertex3f(0.0f, 0.5f, -4.0f); // upper vertex
	glEnd();
	// debug camera
	int speed = ceil(100*dt);

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(float dt)
{
	
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

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * screenSize;
	rect.y = (int)(camera.y * speed) + y * screenSize;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= screenSize;
	rect.h *= screenSize;

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOGCHAR("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * screenSize);
		rec.y = (int)(camera.y + rect.y * screenSize);
		rec.w *= screenSize;
		rec.h *= screenSize;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOGCHAR("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
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