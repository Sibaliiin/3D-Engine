#include	"SIB.h"

#include	<SDL2/SDL.h>

#include	<stdio.h>
#include	<stdbool.h>

void print_signature()
{
	printf("This program was written by István Sibalin\nNovember 5. 2025\n");
	printf("SDL Window boilerplate: Programming Rainbow\n");
	printf("https://github.com/ProgrammingRainbow/Beginners-Guide-to-SDL2-in-C\n");	
}

int generate_random_numbers(int list[256], int r)
{
	for (int i=0; i<256; i++)
	{
		r = rand()%256;
		list[i] = r;
	}

	return *list;
}
	
void game_cleanup	(Engine *engine, int exit_status)
{
	SDL_DestroyRenderer(engine->renderer);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
	exit(exit_status);
}

bool sdl_initialize	(Engine *engine) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		fprintf(stderr, "Error initializing SDL: %s\n",
		SDL_GetError());

		return true;	
	}

	engine->window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0);
	if (!engine->window)
	{
		fprintf(stderr, "Error creating window: %s\n",
		SDL_GetError());

		return true;
	}

	engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
	if (!engine->renderer)
	{
		fprintf(stderr, "Error creating renderer: %s\n",
		SDL_GetError());

		return true;
	}

	return false;
}

void draw_triangle(Engine engine, triangle t, int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(engine.renderer, r, g, b, a);
	SDL_RenderDrawLine(engine.renderer, t.p1.x, t.p1.y, t.p2.x, t.p2.y);
	SDL_RenderDrawLine(engine.renderer, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
	SDL_RenderDrawLine(engine.renderer, t.p3.x, t.p3.y, t.p1.x, t.p1.y);
}
