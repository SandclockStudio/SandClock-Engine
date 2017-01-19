#ifndef __Timer_H__
#define __Timer_H__

#include "SDL\include\SDL.h"

class SimpleTimer
{
public:
	SimpleTimer()
	{}

	Uint32 start() 
	{
		init = SDL_GetTicks();
		stopTimer = false;
		return init;
	}

	Uint32 read() 
	{
		if (stopTimer == true)
			return time;
		return SDL_GetTicks() - init;
	}

	Uint32 stop()
	{
		lol = SDL_GetTicks();
		if (stopTimer == false)
			time = SDL_GetTicks() - init;
		stopTimer = true;
		return time;
	}
	void reset()
	{
		stopTimer = false;
		init = 0;
	}

public:
	bool stopTimer;
	Uint32 time,init;
	Uint32 lol;

};

#endif