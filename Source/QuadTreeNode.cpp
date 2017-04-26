#include "QuadTreeNode.h"
#include "GameObject.h"
#include "Globals.h"

void QuadTreeNode::Create(AABB limits)
{
	root = new NodeTree();
	root->parent = nullptr;
	root->name = "root";	
	root->nodeBoundingBox = AABB(limits);
	root->nodeBoundingBoxSize = root->nodeBoundingBox.Size();
	
}

void QuadTreeNode::CleanUp()
{

	root->CleanUp();
	delete(root);
}

void NodeTree::CleanUp()
{
	//Me elimino normalmente
	if (childs.size() != 0)
	{
		for (size_t i = 0; i < childs.size(); i++)
		{
			childs[i]->CleanUp();
			delete(childs[i]);
		}
	}
	childs.clear();

	if (gameObjects.size() != 0)
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			//if (gameObjects[i] != NULL)
				//RELEASE(gameObjects[i]);
		}
	}

	
	gameObjects.clear();

	
}

void NodeTree::DebugDraw()
{
	float3 corners[8];
	nodeBoundingBox.GetCornerPoints(corners);

	float3 b1 = nodeBoundingBox.minPoint;
	float3 b2 = nodeBoundingBox.maxPoint;
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

	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->DrawBoundingBox();
	}

	for (size_t j = 0; j < childs.size(); j++) 
	{
		childs[j]->DebugDraw();
	}

}

void QuadTreeNode::Insert(GameObject* gameObject) 
{
	//Comprobar que el gameobject este dentro de la bounding box
	if (gameObject->boundingBox.Intersects(root->nodeBoundingBox));
	{
		
		if (root->capacity == root->bucketSpace && root->childs.size() == 0)
		{			

			// tendremos que subdividir la bounding box en 8 partes
			for (int i = 0; i < 8; i++)
			{

				//Creamos un nodo
				NodeTree * child = root->Create(i, root);

				//Añadimos los nuevos hijos al padre una vez asignados
				for (size_t j = 0; j < root->gameObjects.size(); j++)
				{
					// Por cada uno de los 8 nodos y cada uno de los gameobjects tenemos que hacer la comprobacion
					// Dentro se comprueba si entra el gameObject en el hijo
					child->Insert(root->gameObjects[j], i);

				}

				//Insertamos el gameObject que le pasamos
				child->Insert(gameObject, i);

				//Añadimos al padre
				root->childs.push_back(child);
				
			}
			// La memoria no se libera, asi que hay que liberarlar una vez redimensionado
			root->gameObjects.clear();


		}
		else
		{
			if (root->childs.size() == 0)
			{
				root->capacity++;
				root->gameObjects.push_back(gameObject);
			}
			else
			{
				//Para cada hijo meter de forma recursiva
				for (size_t i = 0; i < root->childs.size(); i++)
				{
					root->childs[i]->Insert(gameObject, i);
				}
			}
			
		}

	}

}


NodeTree* NodeTree::Create(int indice, NodeTree *  parent)
{

	float3 centro = parent->nodeBoundingBox.CenterPoint();

	NodeTree * child = new NodeTree();
	child->capacity = 0;
	child->parent = parent;
	//child->name = gameObject->GetName().C_Str();

	float3 auxSize = parent->nodeBoundingBoxSize / 4;


	switch (indice)
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

	child->nodeBoundingBoxSize = child->nodeBoundingBox.Size();

	return child;
}

bool NodeTree::Insert(GameObject * gameObject, int indice)
{

	//Comprobar que introducimos el hijo correctamente

	if (gameObject->boundingBox.Intersects(nodeBoundingBox))
	{
		if (capacity == bucketSpace && childs.size() == 0)
		{
			for (int i = 0; i < 8; i++)
			{
				//Subdividimos
				//Creamos un nodo
				NodeTree * child = Create(i, this);
				//Añadimos los nuevos hijos al padre una vez asignados


				for (size_t j = 0; j < gameObjects.size(); j++)
				{
					// Por cada uno de los 8 nodos y cada uno de los gameobjects tenemos que hacer la comprobacion
					// Dentro se comprueba si entra el gameObject en el hijo
					Insert(gameObjects[j], i);


					

				}

				//Añadimos el gameObject actual
				Insert(gameObject, i);

				childs.push_back(child);

				// La memoria no se libera, asi que hay que liberarlar una vez redimensionado


			}

			gameObjects.clear();
		}
		else
		{
			//Si no tenemos hijos añadimos normalmente
			if (childs.size() == 0) 
			{
				capacity++;
				gameObjects.push_back(gameObject);
			}
			else
			{
				//Para cada hijo meter de forma recursiva el gameObject actual
				for (size_t i = 0; i < childs.size(); i++)
				{
					childs[i]->Insert(gameObject, i);
				}
			}

		}

		return true;
		
	}



	return false;
}
