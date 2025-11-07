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
	
	// defining a triangle
	vec3 point1 = {50, 50, 0};
	vec3 point2 = {100, 100, 0};
	vec3 point3 = {50, 100, 0};

	triangle tri = {point1, point2, point3};

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
		
		//SDL_RenderDrawRect(engine.renderer, &rect);
		//SDL_RenderDrawLine(engine.renderer, 50, 50, 300, 300);
		draw_triangle(engine, tri, 255, 0, 0, 255);		
		// render everything
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
