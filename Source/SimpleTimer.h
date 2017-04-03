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
		pauseTimer = false;

		return init;
	}

	Uint32 read() 
	{
		if (stopTimer == true || pauseTimer == true)
			return time;
		return SDL_GetTicks() - init;
	}

	Uint32 stop()
	{
		if (stopTimer == false)
			time = SDL_GetTicks() - init;
		stopTimer = true;
		return time;
	}
	Uint32 pause()
	{
		if (pauseTimer == false)
			time = SDL_GetTicks() - init;
		pauseTimer = true;
		return time;
	}
	void reanude()
	{
		pauseTimer = false;
		init = SDL_GetTicks()-time;
	}
	void reset()
	{
		stopTimer = false;
		init = 0;
	}

public:
	bool stopTimer, pauseTimer;
	Uint32 time,init;

};

#endif