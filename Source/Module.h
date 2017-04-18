#ifndef __MODULE_H__
#define __MODULE_H__

class Application;
struct Collider;

class Module
{
public:

	Module(bool active = true) : active(active)
	{}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return active;
	}

	 bool Enable()
	{
		if(active == false)
			return active = Start();

		return true;
	}
	 bool Pause()
	 {
		 if (active == true)
			return active = false;
	 }
	 void oneFrame()
	 {

		 oneFramePass = true;
			

	 }
	 bool Continue()
	 {
		 if (active == false)
			 return active = true;
	 }
	 bool Disable()
	 {
		 if(active == true)
			 return active = !CleanUp();

		 return true;
	 }

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}

	//Callbacks ---
	virtual void OnCollision(Collider* col1, Collider* col2)
	{ }

	bool fpsDependent = false;
	bool oneFramePass = false;

	bool gameModule = false;

private:
	bool active = true;
};

#endif // __MODULE_H__