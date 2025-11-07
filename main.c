#include	<SDL2/SDL.h>

#include	<stdio.h>
#include	<stdbool.h>

#include	"SIB.h"

// initializing the rectangle
SDL_Rect rect;

int main()
{
	Engine engine =	{NULL, NULL};

	// defining the rectangle
	rect.w = 50;
	rect.h = 50;
	rect.x = 100;
	rect.y = 50;

	
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
		
		// set the background color to "black"
		SDL_SetRenderDrawColor(engine.renderer, 0, 0, 0, 255);	
		SDL_RenderClear(engine.renderer);
	
		// set the color to red, and draw a rectangle
		SDL_SetRenderDrawColor(engine.renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(engine.renderer, &rect);

		// render everything
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
