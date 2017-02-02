#ifndef __TIMER_H_
#define  __TIMER_H_

#include <time.h>
#include "SDL/include/SDL.h"

class Timer
{
	public:

		float t1,t2;
		bool stopTimer = true;

	public:

		Timer()
		{}

		~Timer()
		{}

		void start()
		{
			stopTimer = false;
			t1 = (float)SDL_GetPerformanceCounter();
		}

		float read()
		{
			if (!stopTimer)
				return (float)((SDL_GetPerformanceCounter() - t1)  / SDL_GetPerformanceFrequency());
			else
				return t2;
		}

		float stop()
		{
			stopTimer = true;
			t2 = (float)((SDL_GetPerformanceCounter() - t1) ) /( SDL_GetPerformanceFrequency());
			return t2;
		}

};

#endif