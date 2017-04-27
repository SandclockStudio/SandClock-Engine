#ifndef __QUADTREE_H
#define __QUADTREE_H

#include <vector>
#pragma comment(lib, "MathGeoLib.lib") 
#include "MathGeoLib.h"

class GameObject;


struct NodeTree 
{
	//my gameObject
	GameObject * gameObject;
	//my parent
	NodeTree * parent;
	
	AABB nodeBoundingBox;

	float3 nodeBoundingBoxSize;

	int bucketSpace = 4;

	std::vector<NodeTree*> childs;
	
	std::vector<GameObject*> gameObjects;

	std::string name;
	int capacity;

	bool Insert(GameObject *, int indice);
	NodeTree* Create(int indice, NodeTree* parent);
	void DebugDraw();
	void CleanUp();
};

class QuadTreeNode
{
	public:
		void Create(AABB limits);
		void Clear();
		void Insert(GameObject*);
		void CleanUp();

	public:
		//std::vector<NodeTree*> objects;
		NodeTree * root;
		
		
};
#endif
