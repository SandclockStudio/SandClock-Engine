#include "GrassBillboard.h"

GrassBillboard::GrassBillboard()
{
	float rand1, rand2, rand3, rand4;

	billboards.clear();

	//Generate random
	for (int i = 0; i < 100; i++)
	{
		rand3 = (rand() % 10 >= 5) ? 1 : -1;
		rand4 = (rand() % 10 >= 5) ? 1 : -1;
		rand1 = rand() % 10 * rand3;
		rand2 = rand() % 10 * rand4;

		float3 pos = float3(rand1, 1.0, rand2);
		billboards.push_back(Billboard(1, pos));
	}
}

GrassBillboard::~GrassBillboard()
{
	billboards.clear();
}

bool GrassBillboard::Init()
{
	for (size_t i = 0; i < billboards.size(); i++)
	{
		billboards[i].Init();
	}
	return true;
}

bool GrassBillboard::Draw()
{
	for (size_t i = 0; i < billboards.size(); i++)
	{
		billboards[i].Draw();
	}
	return true;
}

bool GrassBillboard::Update(Frustum frustum)
{
	std::sort(billboards.begin(), billboards.end(), Billboard::less_than_key());
	for (size_t i = 0; i < billboards.size(); i++)
	{
		billboards[i].Update(frustum);
	}
	return true;
}

void GrassBillboard::ComputeQuad(Frustum frustum)
{
	for (size_t i = 0; i < billboards.size(); i++)
	{
		billboards[i].ComputeQuad(frustum);
	}

}
