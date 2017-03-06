#ifndef __COMPONENT_H
#define __COMPONENT_H

class GameObject;


enum type {
	TRANSFORM,
	MATERIAL,
	MESH,

	NONE
};

class Component
{
public:

	Component(bool active = true) : active(active)
	{}

	virtual ~Component()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	bool Enable()
	{
		return active = true;
	}

	bool Disable()
	{
		return active = false;
	}

	virtual bool Update()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

private:
	bool active = true;

public:
	GameObject* myGo;
	type componentType = NONE;
	int ID = -1;
};

#endif // __COMPONENT_H