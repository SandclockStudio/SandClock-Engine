#include "QuadTreeNode.h"
#include "GameObject.h"

void QuadTreeNode::Create(AABB limits)
{
	root = new NodeTree();
	root->parent = nullptr;
	root->name = "root";	
	root->nodeBoundingBox = AABB(limits);
	root->nodeBoundingBoxSize = root->nodeBoundingBox.Size();
	
}

void QuadTreeNode::Insert(GameObject* gameObject, NodeTree * parent) 
{
	//Comprobar que el gameobject este dentro de la bounding box
	if (gameObject->boundingBox.Intersects(parent->nodeBoundingBox));
	{
		
		if (parent->capacity == bucketSpace)
		{

			float3 centro = parent->nodeBoundingBox.CenterPoint();

			// tendremos que subdividir la bounding box en 8 partes
			for(int i = 0; i < 8;i++)
			{

				//Creamos un nodo
				NodeTree * child = new NodeTree();
				child->capacity = 0;
				child->parent = parent;
				float3 auxSize = parent->nodeBoundingBoxSize/4;

				switch (i)
				{
				case 0:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x + auxSize.x, centro.y + auxSize.y, centro.z + auxSize.z), auxSize));				
					break;
				case 1:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x + auxSize.x, centro.y - auxSize.y, centro.z + auxSize.z), auxSize));
					break;
				case 2:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x - auxSize.x, centro.y + auxSize.y, centro.z + auxSize.z), auxSize));
					break;
				case 3:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x - auxSize.x, centro.y - auxSize.y, centro.z + auxSize.z), auxSize));
					break;
				case 4:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x + auxSize.x, centro.y + auxSize.y, centro.z - auxSize.z), auxSize));
					break;
				case 5:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x + auxSize.x, centro.y - auxSize.y, centro.z - auxSize.z), auxSize));
					break;
				case 6:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x - auxSize.x, centro.y + auxSize.y, centro.z - auxSize.z), auxSize));
					break;
				case 7:
					child->nodeBoundingBox = AABB(Sphere(float3(centro.x - auxSize.x, centro.y - auxSize.y, centro.z - auxSize.z), auxSize));
					break;


				default:
					break;
				}

				parent->childs.push_back(child);



				//Insert(gameObject, child);

				//Obtenemos los 4 gameobjects y comprobamos en que lugar se insertan


				//Añadimos los nuevos hijos al padre una vez asignados
				
					
			}

			for (int j = 0; j < parent->gameObjects.size(); j++)
			{
				Insert(parent->gameObjects[i],)
			}



		}
		else
		{
			parent->capacity++;
			parent->gameObjects.push_back(gameObject);
		}

	}

}

void QuadTreeNode::DebugDraw()
{
	float3 * corners;
	root->nodeBoundingBox.GetCornerPoints(corners);

	float3 b1 = root->nodeBoundingBox.minPoint;
	float3 b2 = root->nodeBoundingBox.maxPoint;
	float3 b3 = float3(b1.x, b1.y, b2.z);
	float3 b4 = float3(b1.x, b2.y, b1.z);
	float3 b5 = float3(b2.x, b1.y, b1.z);
	float3 b6 = float3(b1.x, b2.y, b2.z);
	float3 b7 = float3(b2.x, b1.y, b2.z);
	float3 b8 = float3(b2.x, b2.y, b1.z);


	glBegin(GL_LINES);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b2.x, b2.y, b2.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b8.x, b8.y, b8.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b4.x, b4.y, b4.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b6.x, b6.y, b6.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b3.x, b3.y, b3.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b7.x, b7.y, b7.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b5.x, b5.y, b5.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b1.x, b1.y, b1.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b6.x, b6.y, b6.z);
	glVertex3f(b3.x, b3.y, b3.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b2.x, b2.y, b2.z);
	glVertex3f(b7.x, b7.y, b7.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b8.x, b8.y, b8.z);
	glVertex3f(b5.x, b5.y, b5.z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(b4.x, b4.y, b4.z);
	glVertex3f(b1.x, b1.y, b1.z);

	glLineWidth(20.0f);
	glEnd();

	delete(corners);
}