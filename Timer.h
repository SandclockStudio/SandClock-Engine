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
				return (double)((SDL_GetPerformanceCounter() - t1) * 1000 / SDL_GetPerformanceFrequency());
			else
				return t2;
		}

		Uint64 stop()
		{
			stopTimer = true;
			t2 = (double)((SDL_GetPerformanceCounter() - t1) * 1000 / SDL_GetPerformanceFrequency());
			return t2;
		}

};

#endif