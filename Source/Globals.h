#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//#include "MemLeaks.h"
#include "SDL/include/SDL_rect.h"
#define LOGCHAR(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define CHECKERS_HEIGHT 32
#define CHECKERS_WIDTH 32

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

namespace MY {
	typedef unsigned int Uint;
}

// Useful typedefs ---------
typedef unsigned int uint;

// Deletes a buffer
#define RELEASE( x ) \
    {									  \
       if( x != nullptr )   \
       {						      \
         delete x;                  \
	     x = nullptr;             \
       }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{                              \
       if( x != nullptr )              \
       {                            \
           delete[] x;                \
	       x = nullptr;                    \
		 }                            \
                              \
	 }

// Configuration -----------
/*#define SCREEN_SIZE 3
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 220
#define FULLSCREEN false
#define VSYNC true*/
#define JSONCONFIG "config.json"

#endif //__GLOBALS_H__