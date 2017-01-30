#ifndef __TIMER_H_
#define  __TIMER_H_

#include <time.h>
#include "SDL/include/SDL.h"

class Timer
{
	public:

		double t1,t2;
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

		double read()
		{
			if (!stopTimer)
				return (double)((SDL_GetPerformanceCounter() - t1)  / SDL_GetPerformanceFrequency());
			else
				return t2;
		}

		double stop()
		{
			stopTimer = true;
			t2 = (double)((SDL_GetPerformanceCounter() - t1) ) /( SDL_GetPerformanceFrequency());
			return (double)((SDL_GetPerformanceCounter() - t1) )/ (SDL_GetPerformanceFrequency());
		}

};

#endif