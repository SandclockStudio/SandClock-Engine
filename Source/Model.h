#ifndef _MODEL_H_
#define _MODEL_H_

#include <assimp/include/assimp/scene.h>
#include <vector>
#include <MathGeoLib.h>
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
	void Draw2();
	//void LoadGLTextures(const aiScene* scene, const char* pModelPath);
	void LoadAssimp(const char * path,std::vector<unsigned short> & indices,std::vector<math::vec> & vertices,std::vector<math::float2> & uvs,	std::vector<math::vec> & normals);

private:

};

#endif /* _MODEL_H_ */