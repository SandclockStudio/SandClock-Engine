#include "Application.h"
#include "JsonParser.h"
#include "ModuleEditor.h"
#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_sdl_gl3.h"
#include "../Libraries/OpenGL/include/GL/glew.h"
#pragma comment (lib, "opengl32.lib") 
#include "ModuleWindow.h"
#include "ModuleScene.h"
#include "ComponentTransform.h"


ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	ImGui_ImplSdlGL3_Init(App->window->window);
	return true;
}

update_status ModuleEditor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float dt)
{
	DrawConsole();
	DrawTree();
	DrawProperties();
	DrawPlayMenu();
	if(fps_log.size() != 0)
		DrawFps();
	return DrawMenu();
}

update_status ModuleEditor::PostUpdate(float dt)
{
	//ImGui::ShowTestWindow();

	return UPDATE_CONTINUE;
}

void ModuleEditor::DrawConsole()
{
	ImGui::SetNextWindowPos(ImVec2(0, App->window->screenHeight*App->window->screenSize - 200));
	ImGui::SetNextWindowSize(ImVec2(App->window->screenWidth*App->window->screenSize-400, 200));
	ImGui::Begin("Console", NULL, 0);
	ImGui::TextUnformatted(Buf.begin());
	ImGui::End();
}

void ModuleEditor::DrawFps()
{
	ImGui::SetNextWindowPos(ImVec2(App->window->screenWidth*App->window->screenSize-350, App->window->screenHeight*App->window->screenSize - 180));
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Histogram", NULL, 0);
	ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, "Frames", 0.0f, 100.0f, ImVec2(310, 100));
	ImGui::End();
}

void ModuleEditor::AddFps(float fps)
{
	fps_log.push_back(fps);
}

void ModuleEditor::AddLog(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	Buf.appendv(fmt, args);
	Buf.appendv("\n", nullptr);
	va_end(args);
}


bool ModuleEditor::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}


void ModuleEditor::InputHandler(SDL_Event* event)
{
	ImGui_ImplSdlGL3_ProcessEvent(event);
}

update_status ModuleEditor::DrawMenu()
{

	update_status ret = UPDATE_CONTINUE;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New");
			ImGui::MenuItem("Load");
			ImGui::MenuItem("Save");
			if (ImGui::MenuItem("Quit"))
			{
				ret = UPDATE_STOP;
			}
			ImGui::EndMenu();

		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Documentation"))
			{
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Wiki"))
			{
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("Report a bug"))
			{
				ret = UPDATE_STOP;
			}
			if (ImGui::MenuItem("About"))
			{
				ret = UPDATE_STOP;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Configuration"))
		{
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
			{
				App->window->setFullScreen(fullscreen);
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("Resizable", &resizable))
			{
				App->window->setResizable(resizable);
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	return ret;
}


void ModuleEditor::DrawTree()
{
	int id = 0;
	bool begin = true;
	int node_clicked = -1;

	GameObject * go = nullptr;
	ImGui::SetNextWindowPos(ImVec2(0, 20));
	ImGui::SetNextWindowSize(ImVec2(App->window->screenWidth, App->window->screenHeight ));

	ImGui::Begin("Hierarchy", &begin, ImVec2(App->window->screenWidth / 3, App->window->screenHeight / 1.58f), -1.0f, ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_ChildWindowAutoFitY | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	

	ImGui::Unindent(15.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3); // Increase spacing to differentiate leaves from expanded contents.

	if (App->scene_intro != nullptr)
	{
		if (App->scene_intro->root != nullptr)
		{
			int selection_mask = (1 << 2);
			int tama = App->scene_intro->root->getChilds().size();
			for (int i = 0; i < tama; ++i)
			{

				GameObject * go = App->scene_intro->root->getChilds()[i];


				ImGuiTreeNodeFlags node_flags =( ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick  );
				ImGuiTreeNodeFlags node_flags_leaf = (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf );

				if (go->getChilds().size() == 0) 
				{
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)id, node_flags_leaf, go->GetName().C_Str());
					if (ImGui::IsItemClicked())
					{
						node_clicked = id;
						go = App->scene_intro->root->getChilds()[i];
						selected = go;

					}
					id++;
					//ImGui::TreePop();
				}
				else
				{
					bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)id, node_flags, go->GetName().C_Str());
					if (ImGui::IsItemClicked())
					{
						node_clicked = id;
						go = App->scene_intro->root->getChilds()[i];
						selected = go;

					}
					id++;


					if (node_open)
					{
						Children(App->scene_intro->root->getChilds()[i], id);
					}	
				}


			}
		}
		

	}

	ImGui::PopStyleVar();
	ImGui::Indent(15.0f);
	ImGui::End();

}

void ModuleEditor::Children(GameObject * go, int &ptr_id)
{
	bool node_open;
	int node_clicked = -1;
	int selection_mask = (1 << 2);


	for (int i = 0; i < go->getChilds().size(); i++)
	{
		ImGuiTreeNodeFlags node_flags = (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick );
		ImGuiTreeNodeFlags node_flags_leaf = (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf);
		GameObject * child = go->getChilds()[i];



		if (child->getChilds().size() == 0) 
		{
			node_open = ImGui::TreeNodeEx((void*)(intptr_t)ptr_id, node_flags_leaf, child->GetName().C_Str());
			if (ImGui::IsItemClicked())
			{
				node_clicked = ptr_id;
				go = child;
				selected = go;

			}
			ptr_id++;
		}
		else
		{
			node_open = ImGui::TreeNodeEx((void*)(intptr_t)ptr_id, node_flags, child->GetName().C_Str());
			if (ImGui::IsItemClicked())
			{
				node_clicked = ptr_id;
				go = child;
				selected = go;
			}
			ptr_id++;

			if (node_open)
			{
				Children(child, ptr_id);
				
			}		
		}
	}

	ImGui::TreePop();
}

void ModuleEditor::DrawProperties()
{
	bool begin = true;
	ImGui::SetNextWindowPos(ImVec2(App->window->screenWidth*App->window->screenSize-400, 20));
	ImGui::SetNextWindowSize(ImVec2(App->window->screenWidth, App->window->screenHeight));

	ImGui::Begin("Properties", &begin, ImVec2(App->window->screenWidth / 3, App->window->screenHeight / 1.58f), -1.0f, ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_ChildWindowAutoFitY | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	
	ImGui::Unindent(15.0f);
	if (selected != nullptr)
	{
		GameObject* gOSelected = selected;
		//Aquí falla al coger la posición y la rotación que la recoge el gameobject del componente
		if (ImGui::CollapsingHeader("Local Transformation", ImGuiTreeNodeFlags_DefaultOpen))
		{
			aiVector3D pos = gOSelected->getPosition();
			aiQuaternion rot = gOSelected->getRotation();
			Quat rotation = Quat(rot.x, rot.y, rot.z, rot.w);
			float3 rota = rotation.ToEulerXYZ() * 180.0f / pi;
			aiVector3D scale = gOSelected->getScale();
			//Una vez se recoja tiene que tener el gameObject una funión para poner la posición y la rotación que se le pase
			if (ImGui::DragFloat3("Position", (float*)&pos, 0.01f))
			{
				gOSelected->setPosition(pos);
			}
				
			if (ImGui::DragFloat3("Rotation", (float*)&rota,0.6f))
			{
				gOSelected->setRotation(Quat::FromEulerXYZ(rota.x*pi / 180.0f, rota.y*pi / 180.0f, rota.z*pi / 180.0f));
			}

			if (ImGui::DragFloat3("Scale", (float*)&scale, 0.05f))		
			{
				gOSelected->setScale(scale);
			}
		}
	}
	ImGui::End();

}

void ModuleEditor::DrawPlayMenu()
{
	//ImGui::SetNextWindowPos(ImVec2(App->window->screenWidth*App->window->screenSize, App->window->screenHeight*App->window->screenSize));
	ImGui::SetNextWindowSize(ImVec2(500, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("PlayMenu");
	if (ImGui::Button("Play"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{

	}
	
	ImGui::SameLine();
	if (ImGui::Button("Update"))
	{

	}
	//ImGui::Text("Window title");
	ImGui::End();
}