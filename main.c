#include	"SIB.h"

// initializing the rectangle
SDL_Rect rect;

// making a 4x4 projection matrix
float matProj[4][4];

int main()
{
	srand(time(NULL));
	
	printf("m[0][0] = %f\n", matProj[0][0]);

	int rSize = 16;
	int random_numbers[(rSize*rSize)];
	
	int r = rand()%256;

	generate_random_numbers(random_numbers, r);
	
	printf("size of random numbers = %d\n", (int)sizeof(random_numbers));

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
	
	// attemtping to make a 16*16 grid, which will be a terrain.
	// it will consist of 16*16 points.
	// every coordinate will be (0, 0, 0), (1, 0, 0), ... , (15, 0, 0) , (0, 0, 1), (1, 0, 1), ... , (15, 0, 15).
	// we will use the random number generation, and put number[i] into point[i].y. y will be the height of the given "node".
	vec3 pTerrain[16*16];
	
	for (int row=0; row<16; row++)
	{
		for (int col=0; col<16; col++)
		{
			pTerrain[(16*row)+col].x = col*10;
			pTerrain[(16*row)+col].y = row*10;
			pTerrain[(16*row)+col].z = (1.0f/256.0f) * random_numbers[(16*row)+col];
		}
	}

	triangle terrainTop[15*15];
	triangle terrainBot[15*15];

	// "top-left" triangles
	for (int row=0; row<15; row++)
	{
		for (int col=0; col<15; col++)
		{
			terrainTop[(15*row)+col].p1 = pTerrain[(16*row)+col]; 
			terrainTop[(15*row)+col].p2 = pTerrain[(16*row)+col+1];
			terrainTop[(15*row)+col].p3 = pTerrain[(16*(row+1))+col];     
		}
	}
	// "bottom-right" triangles
	for (int row=0; row<15; row++)
        {
                for (int col=0; col<15; col++)
                {
                        printf("terrain[%d] = \n", (15*row)+col);
                        terrainBot[(15*row)+col].p1 = pTerrain[(16*row)+col+1];
                        terrainBot[(15*row)+col].p2 = pTerrain[(16*(row+1))+col+1];
                        terrainBot[(15*row)+col].p3 = pTerrain[(16*(row+1))+col];                        
                }
        }


	// print the pTerrain points	
	for (int i=0; i<256; i++)
	{
		printf("pTerrain[%d] = %f, %f, %f\n", i,  pTerrain[i].x, pTerrain[i].y, pTerrain[i].z);
	}


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
	
				SDL_SetRenderDrawColor(engine.renderer,
							random_numbers[(rSize*i)+j],
							random_numbers[(rSize*i)+j],
							random_numbers[(rSize*i)+j],
							255);
				SDL_RenderFillRect(engine.renderer, &rect);
				rect.x += 10;	
			}
			rect.y += 10;
			rect.x = 40;
		}	
		// draw the terrain mesh
		for (int i=0; i<15*15; i++)
		{	
			draw_triangle(engine, terrainTop[i], 255, 255, 255, 255);
			draw_triangle(engine, terrainBot[i], 255, 255, 255, 255);		
		
		}	
		//draw_triangle(engine, terr1, 255, 255, 255, 255);
		// render everything
		SDL_RenderPresent(engine.renderer);

		SDL_Delay(16);

		rect.x = 40;
		rect.y = 40;
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}
