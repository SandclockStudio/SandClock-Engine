#include "Component.h"
#include "Billboard.h"
#include "Application.h"



struct Particle 
{
	float3 position;
	float3 velocity;
	float lifetime;
	bool dead;

	float3 positions[4];
	float3 normal;
	float3 up;
	float3 right;
};

typedef std::vector<Particle> ParticlePool;
typedef std::vector<Billboard> BillBoardPool;
typedef std::vector<unsigned> ParticleList;

class ComponentParticle : public Component
{
public:
	ComponentParticle();
	~ComponentParticle();
	void Init(unsigned max_particles, const char * file);
	bool Update(Frustum f);
	bool Draw();

	void ComputeQuad(Frustum f);


private:
	GLuint loadImages(const char*);

private:

	
	ParticlePool particles;
	ParticleList alive;
	ParticleList dead;
	BillBoardPool billboards;

	//aiVector2D emit_area;
	unsigned falling_time = 0;
	unsigned accum_elapsed = 0;
	float falling_height = 0;
	unsigned texture = 0;

	

};
