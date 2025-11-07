#ifndef	SIB_ENGINE_H
#define	SIB_ENGINE_H

#include	<SDL2/SDL.h>

// engine structure
typedef struct
{
        SDL_Window      *window;
        SDL_Renderer    *renderer;
} Engine;

#endif
