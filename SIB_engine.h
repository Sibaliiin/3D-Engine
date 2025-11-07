#ifndef	SIB_ENGINE_H
#define	SIB_ENGINE_H

#include	<SDL2/SDL.h>

#define WINDOW_TITLE    "Window"
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

// engine structure
typedef struct
{
        SDL_Window      *window;
        SDL_Renderer    *renderer;
} Engine;

#endif
