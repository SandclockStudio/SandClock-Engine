#ifndef _MODEL_H_
#define _MODEL_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include "Devil\include\IL\ilut.h"

class Model
{

	const aiScene* scene = 0;
	//GLuint*	textureIds;// pointer to texture Array
public:

	Model();
	~Model();

	void Load(const char* file);
	void Clear();
	void Draw();
	GLuint loadTexture(char * theFileName);


	GLuint img;

private:
	std::vector<int> textureIndex;
};

#endif /* _MODEL_H_ */