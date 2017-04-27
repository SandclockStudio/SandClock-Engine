#include "../Libraries/OpenGL/include/GL/glew.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "SDL/include/SDL.h"
#include "JsonParser.h"
#include "ModuleWindow.h"
#pragma comment(lib, "MathGeoLib.lib") 
#include "MathGeoLib.h"
#include "ModuleCamera.h"
#include "ModuleScene.h"
#pragma comment (lib, "opengl32.lib") 


#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({0, 0}), mouse_motion({0,0})
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	RELEASE_ARRAY(keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOGCHAR("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (LoadConfig() == false)
	{
		LOGCHAR("Problem in the configuration file");
		ret = false;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOGCHAR("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool ModuleInput::Start()
{
	return true;
}

// Called each loop iteration
update_status ModuleInput::PreUpdate(float dt)
{
	static SDL_Event event;

	mouse_motion = {0, 0};
	memset(windowEvents, false, WE_COUNT * sizeof(bool));
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}
	

	while(SDL_PollEvent(&event) != 0)
	{
		App->editor->InputHandler(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_RESIZED:
					{

						//Habra que cambiarlo en el futuro si tenemos mas cámaras
						App->window->screenWidth = event.window.data1;
						App->window->screenHeight = event.window.data2;
						float fovNew = (float)App->window->screenWidth / (float)App->window->screenHeight;
						App->scene_intro->componentCamera->SetAspectRatio(fovNew);
						glViewport(0, 0, (float)App->window->screenWidth, (float)App->window->screenHeight);
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();
						glLoadMatrixf((GLfloat*)App->scene_intro->componentCamera->GetProjectionMatrix());
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();
						glLoadMatrixf((GLfloat*)App->scene_intro->componentCamera->GetViewMatrix());

						break;
					}
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

			case SDL_MOUSEMOTION:
				mouse_motion.x = event.motion.xrel / screenSize;
				mouse_motion.y = event.motion.yrel / screenSize;
				mouse.x = event.motion.x / screenSize;
				mouse.y = event.motion.y / screenSize;
			break;
		}
	}

	if(GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOGCHAR("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool ModuleInput::GetWindowEvent(EventWindow ev) const
{
	return windowEvents[ev];
}

const iPoint& ModuleInput::GetMousePosition() const
{
	return mouse;
}

const iPoint& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}

bool ModuleInput::LoadConfig()
{
	bool return_value = true;

	if (App->json_parser->LoadObject("Config.App"))
	{
		//screenWidth = App->json_parser->GetInt("Width");
		//screenHeight = App->json_parser->GetInt("Height");
		screenSize = App->json_parser->GetInt("Size");
		//vsync = App->json_parser->GetBool("Vsync");
		return_value = App->json_parser->UnloadObject();
	}

	return return_value;

}