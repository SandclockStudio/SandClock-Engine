#include "GameObject.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "ComponentMesh.h"
#include "Application.h"
#include <vector>
#include "Brofiler/Brofiler.h"
#pragma comment(lib, "ProfilerCore64.lib")
#include "ComponentRigidbody.h"
#include "Application.h"

void GameObject::CleanUp()
{
	delete(corners);

	for (size_t i = 0; i < components.size();i++)
	{
		components[i]->CleanUp();
		RELEASE(components[i]);
	}
	components.clear();
}

void GameObject::AddComponent(Component * component)
{

		boundingBox = AABB();
		boundingBox.SetNegativeInfinity();
		components.push_back(component);
		component->setGameObject(this);


}


void GameObject::DeleteComponent(Component * component)
{
	/*
	for (int i = 0; i < components.size(); ++i)
	{
	if(components[i]->ID == component->ID)
	components.erase(componentes[i]);
	}
	*/
}

bool GameObject::Update(Frustum f)
{
	BROFILER_CATEGORY("Update", Profiler::Color::RosyBrown);
	glPushMatrix();
	if (typeRender != RenderType::UIRENDER)
	{
		for (size_t i = 0; i < components.size(); ++i)
		{
			components[i]->Update(f);

			if (components.size() == 1)
			{
				glPopMatrix();
			}
		}

		if (childs.size() > 0)
		{
			for (size_t i = 0; i < childs.size(); ++i)
			{

				if (intersectFrustumAABB(f, childs[i]->boundingBox))
					childs[i]->Update(f);
			}
		}
	}

	return true;
}

bool GameObject::UpdateUI()
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->UpdateUI();
	}

	return true;
}

bool GameObject::PreUpdate()
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->PreUpdate();
	}
	if (childs.size() > 0)
	{
		for (size_t i = 0; i < childs.size(); ++i)
		{
				childs[i]->PreUpdate();
		}
	}
	return true;
}

void GameObject::DrawBoundingBox()
{
	
	boundingBox.GetCornerPoints(corners);

	float3 b1 = boundingBox.minPoint;
	float3 b2 = boundingBox.maxPoint;
	float3 b3 = float3(b1.x, b1.y, b2.z);
	float3 b4 = float3(b1.x, b2.y, b1.z);
	float3 b5 = float3(b2.x, b1.y, b1.z);
	float3 b6 = float3(b1.x, b2.y, b2.z);
	float3 b7 = float3(b2.x, b1.y, b2.z);
	float3 b8 = float3(b2.x, b2.y, b1.z);


	glBegin(GL_LINES);

	glColor3f(1.0f,1.0f,1.0f);
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
}


GameObject * GameObject::FindGameObject(aiString node)
{
	for (size_t i = 0; i<childs.size(); i++)
		if (childs[i]->GetName() == node)
			return childs[i];
	return nullptr;
}

void GameObject::AddChild(GameObject * node)
{
	childs.push_back(node);
}

GameObject * GameObject::LoadGameObjectMesh(aiNode * node, aiMesh * mesh, const aiScene * scene)
{
	BROFILER_FRAME("Gameobject");
	GameObject * go = new GameObject(node->mName);

	ComponentTransform* transform = new ComponentTransform(true);
	
	transform->LoadTransform(node);
	go->position = transform->pos;
	go->rotation = transform->quat;
	go->scale = transform->scale;
	go->AddComponent(transform);


	ComponentMaterial* material = new ComponentMaterial(true);

	material->LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
	go->AddComponent(material);

	ComponentMesh* m = new ComponentMesh(true);
	go->AddComponent(m);


	
	
	if (node->mName == aiString("g City_building_022") || node->mName == aiString("g City_building_037"))
	{
		rigidBody = App->physics->AddCubeBody(1.0f, go);
	}
	else
		rigidBody = App->physics->AddCubeBody(0.0f, go);

	ComponentRigidbody* rb = new ComponentRigidbody(true, rigidBody);
	rb->rigid_body = rigidBody->getMotionState();
	
	go->AddComponent(rb);


	m->LoadMesh(mesh, scene);



	return go;
}

GameObject* GameObject::LoadGameObject(aiNode * node)
{
	BROFILER_FRAME("Gameobject");
	GameObject * go = new GameObject(node->mName);

	ComponentTransform* transform = new ComponentTransform(true);

	transform->LoadTransform(node);
	go->position = transform->pos;
	go->rotation = transform->quat;
	go->scale = transform->scale;
	go->AddComponent(transform);

	return go;
}

aiVector3D GameObject::getPosition() const
{
	return position;
}

aiQuaternion GameObject::getRotation() const
{
	return rotation;
}

aiVector3D GameObject::getScale() const
{
	return (dynamic_cast<ComponentTransform*>(components[0])->scale);
}

void GameObject::setPosition(aiVector3D newPosition)
{
	position = newPosition;
	if (components.size() > 0)
	{
		dynamic_cast<ComponentTransform*>(components[0])->Translate(newPosition);
	}
}

void GameObject::setRotation(Quat newRotation)
{
	rotation = aiQuaternion(newRotation.w,newRotation.x, newRotation.y, newRotation.z);
	if (components.size() > 0)
	{
		dynamic_cast<ComponentTransform*>(components[0])->Rotate(rotation);
	}
}
	

RenderType GameObject::getRenderType() const
{
	return typeRender;
}

void GameObject::DrawLines()
{

		if (components.size()>0)
		{

			glColor3f(1.0f, 1.0f, 1.0f);
			glDepthRange(0.0, 0.01);
			glLineWidth(2.0f);
			glDisable(GL_LIGHTING);
			glEnable(GL_COLOR_MATERIAL);
			glPushMatrix();

			dynamic_cast<ComponentTransform*>(components[0])->Update2();

			for (size_t i = 0; i < childs.size(); i++)
			{
				glDisable(GL_LIGHTING);
				
				glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(childs[i]->position.x, childs[i]->position.y, childs[i]->position.z);
				glEnd();
				childs[i]->DrawLines();
				glEnable(GL_LIGHTING);

			}
			glPopMatrix();

		}
	
}
	




void GameObject::setScale(aiVector3D newScale)
{
	scale = newScale;
	if (components.size() > 0)
	{
		dynamic_cast<ComponentTransform*>(components[0])->Scale(newScale);
	}

}

void GameObject::setMass(float mass)
{
	if (components.size() > 3)
	{
		dynamic_cast<ComponentRigidbody*>(components[3])->setMass(mass);
	}
}


/**
* Tells whether or not b is intersecting f.
* @param f Viewing frustum.
* @param b An axis aligned bounding box.
* @return True if b intersects f, false otherwise.
*/
bool GameObject::intersectFrustumAABB(Frustum f, AABB box)
{
	if (frustumCulling)
	{
		static const int NUM_PLANES = 6;
		const Plane planes[NUM_PLANES] =
		{ f.GetPlane(0), f.GetPlane(1), f.GetPlane(2), f.GetPlane(3), f.GetPlane(4), f.GetPlane(5) };


		std::vector<float3> points;
		float3 b1 = box.minPoint;
		points.push_back(b1);
		float3 b2 = box.maxPoint;
		points.push_back(b2);
		float3 b3 = float3(b1.x, b1.y, b2.z);
		points.push_back(b3);
		float3 b4 = float3(b1.x, b2.y, b1.z);
		points.push_back(b4);
		float3 b5 = float3(b2.x, b1.y, b1.z);
		points.push_back(b5);
		float3 b6 = float3(b1.x, b2.y, b2.z);
		points.push_back(b6);
		float3 b7 = float3(b2.x, b1.y, b2.z);
		points.push_back(b7);
		float3 b8 = float3(b2.x, b2.y, b1.z);
		points.push_back(b8);
		float3 b9 = box.CenterPoint();
		points.push_back(b9);


		for (size_t j = 0; j < points.size(); j++)
		{
			int out = 0;
			for (int i = 0; i < 6; i++)
			{
				const Plane p = planes[i];

				if (p.SignedDistance(points[j]) < 0)	out++;

			}
			if (out == 6)return true;
		}

		return false;
	}
	else
		return true;
	
	}

void GameObject::setTransformAnimation(aiVector3D scale, aiVector3D position, Quat rotation)
{
	setPosition(position);
	setScale(scale);
	setRotation(rotation);
}

void GameObject::SetRenderType(RenderType type)
{
	typeRender = type;
}



float4x4 GameObject::GetLocalTransformMatrix() const
{
	BROFILER_CATEGORY("GetLocal Transform Matrix", Profiler::Color::Yellow);
	return float4x4::FromTRS(float3(position.x,position.y,position.z),Quat(rotation.x,rotation.y,rotation.z,rotation.w),float3(scale.x,scale.y,scale.z));
}


float4x4 GameObject::GetModelSpaceTransformMatrix()  const
{
	BROFILER_CATEGORY("GetModelSpace Transform Matrix", Profiler::Color::RosyBrown);
	if (root == nullptr)
	{
		return float4x4::identity;
	}
	else
	{
		return root->GetModelSpaceTransformMatrix() * GetLocalTransformMatrix();
	}
}