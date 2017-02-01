#ifndef __TIMER_H_
#define  __TIMER_H_

#include <time.h>
#include "SDL/include/SDL.h"

class Timer
{
	public:

		Uint64 t1,t2;
		bool stopTimer = true;

	public:

		Timer()
		{}

		~Timer()
		{}

		void start()
		{
			stopTimer = false;
			t1 = SDL_GetPerformanceCounter();
		}

		Uint64 read()
		{
			if (!stopTimer)
				return ((SDL_GetPerformanceCounter() - t1)  / SDL_GetPerformanceFrequency());
			else
				return t2;
		}

		Uint64 stop()
		{
			stopTimer = true;
			t2 = ((SDL_GetPerformanceCounter() - t1) ) /( SDL_GetPerformanceFrequency());
			return ((SDL_GetPerformanceCounter() - t1) )/ (SDL_GetPerformanceFrequency());
		}

};

#endif