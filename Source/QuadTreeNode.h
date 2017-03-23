#ifndef __QUADTREE_H
#define __QUADTREE_H

#include <vector>
#include "MathGeoLib.h"

class GameObject;


struct NodeTree 
{
	//my gameObject
	GameObject * gameObject;
	//my parent
	NodeTree * parent;
	//
	AABB nodeBoundingBox;
	//coger la de gameobject y dibujar
	float3 nodeBoundingBoxSize;

	std::vector<NodeTree*> childs;
	
	std::vector<GameObject*> gameObjects;

	std::string name;
	int capacity;
};

class QuadTreeNode
{
	public:
		void Create(AABB limits);
		void Clear();
		void Insert(GameObject*, NodeTree*);
		void DebugDraw();

	public:
		//std::vector<NodeTree*> objects;
		NodeTree * root;
		int bucketSpace = 4;
		
};
#endif
