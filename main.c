#include	<SDL2/SDL.h>

#include	<stdio.h>
#include	<stdbool.h>

#include	"SIB.h"

#define WINDOW_TITLE	"Window"
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

void game_cleanup	(Engine *engine, int exit_status);
bool sdl_initialize	(Engine *engine);

int main()
{
	Engine engine =	{NULL, NULL};

	if (sdl_initialize(&engine))
	{
		game_cleanup(&engine, EXIT_FAILURE);
	}

	printf("Hello world!\n");
	print_signature();
	
	// main while loop
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				game_cleanup(&engine, EXIT_SUCCESS);
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					game_cleanup(&engine, EXIT_SUCCESS);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}	
		SDL_RenderClear(engine.renderer);

		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
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
