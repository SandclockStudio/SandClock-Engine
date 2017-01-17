#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"



ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("");
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* aux = *it;
		if (aux->collider == c1)
		{
			aux->to_delete = true;
		}

		++it;
	}
}


// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false || p->to_delete == true)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->animation.GetCurrentFrame()));
			++it;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y,int vel, particle_type type, COLLIDER_TYPE collider_type)
{

	Particle* p = new Particle(particle);
	p->position.x = x;
	p->position.y = y;
	p->speed.x = vel;
	p->speed.y = 0;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 10, 10 }, collider_type,this);
	}
	active.push_back(p);

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : collider(NULL)
{}


Particle::Particle(const Particle& p) : animation(p.animation), position(p.position), speed(p.speed), collider(p.collider)
{
	t.setFirstTime();
}

Particle::~Particle()
{

}

bool Particle::Update()
{
	bool ret = true;
	t.setSecondTime();

	if (collider != NULL)
	{
		SDL_Rect r = animation.GetCurrentFrame();
		position.x += speed.x;
		collider->SetPos(position.x, position.y);
	}


	return ret;
}



