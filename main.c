#include	"SIB.h"
#include	<time.h>

// initializing the rectangle
SDL_Rect rect;

int main()
{
	srand(time(NULL));
	
	int r = rand();

	printf("random number = %d\n",r);
	int rSize = 32;
	int random_numbers[(rSize*rSize)];

	for (int i=0; i<(rSize*rSize); i++)
	{
		random_numbers[i] = r%256;
		printf("%d\n", r%256);
		r = rand();
	}	
	printf("size of random numbers = %d\n", (int)sizeof(random_numbers));
	
	r = rand()%256;

	Engine engine =	{NULL, NULL};

	// defining the rectangle
	rect.w = 10;
	rect.h = rect.w;
	rect.x = 40;
	rect.y = 40;
	
	// defining a triangle
	vec3 point1 = {50, 50, 0};
	vec3 point2 = {100, 100, 0};
	vec3 point3 = {0, 100, 0};

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

		// draw a gray-scale square. random color.	
		for (int i=0; i<rSize; i++)
		{
			for (int j=0; j<rSize; j++)
			{
	
				SDL_SetRenderDrawColor(engine.renderer, random_numbers[(rSize*i)+j],
								random_numbers[(rSize*i)+j],
								random_numbers[(rSize*i)+j],
								 255);
				SDL_RenderFillRect(engine.renderer, &rect);
				rect.x += 10;	
			}
			rect.y += 10;
			rect.x = 40;
		}	

		draw_triangle(engine, tri, 255, 0, 0, 255);		
		// render everything
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);

		rect.x = 40;
		rect.y = 40;
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
