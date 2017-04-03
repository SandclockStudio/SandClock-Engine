#ifndef __BILLBOARD_H
#define __BILLBOARD_H

#include "IL/ilut_config.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"


#pragma comment (lib, "DevIL.lib") 
#pragma comment (lib, "ILU.lib") 
#pragma comment (lib, "ILUT.lib") 
#pragma comment (lib, "assimp-vc140-mt.lib")
#include <assimp/include/assimp/scene.h>

#include "MathGeoLib.h"



class Billboard
{



public:

	Billboard(int size, float3 pos);
	~Billboard();

	bool Init();
	bool Draw();
	bool Update(Frustum frustum);
	void ComputeQuad(Frustum frustum);

	void DrawBoundingBox();

public:
	float distance;
	struct less_than_key
	{
		inline bool operator() (const Billboard& struct1, const Billboard& struct2)
		{
			return (struct1.distance > struct2.distance);
		}
	};

private:
	GLuint loadImages(const char*);

private:

	unsigned int texture;
	float size;

	float3 pos;
	aiQuaternion quat;

	AABB boundingBox;

	float3 positions[4];



	//○ Normal coincide con el vector entre la posición de la cámara y la posición central del billboard
	//○ Up es fija para el billboard y coincide con el up vector del mundo
	//○ Right es el producto vectorial entre N x R

	float3 normal;
	float3 up;
	float3 right;


};

#endif
