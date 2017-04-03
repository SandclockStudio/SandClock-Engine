#include "Billboard.h"
#include <vector>

class GrassBillboard
{

public:

	GrassBillboard();
	~GrassBillboard();


	bool Init();
	bool Draw();
	bool Update(Frustum frustum);
	void ComputeQuad(Frustum frustum);

public:
	std::vector<Billboard> billboards;
};
