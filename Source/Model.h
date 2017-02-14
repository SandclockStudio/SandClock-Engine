#ifndef _MODEL_H_
#define _MODEL_H_

#include <assimp/include/assimp/scene.h>

class Model
{

	const aiScene* scene = 0;

public:

	Model();
	~Model();

	void Load(const char* file);
	void Clear();
	void Draw();
};

#endif /* _MODEL_H_ */