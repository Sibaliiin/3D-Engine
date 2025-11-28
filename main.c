#include	"SIB.h"
#include	<math.h>

// initializing the rectangle
SDL_Rect rect;

// making a 4x4 projection matrix
float matProj[4][4];

// model vector: put the grid into a desired position
vec3 modelVec;

vec3 SIB_ModelTrans	(vec3 p, vec3 d); 
vec3 SIB_ProjTrans	(vec3 p, float m[4][4], vec3 o);	

int main()
{

	// model vector
	modelVec = (vec3){-8.0f, 2.0f, 0.0f};

	// setting up variables for the projection matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.f;
	float fAspectRatio = (float)SCREEN_HEIGHT/(float)SCREEN_WIDTH;
	float fFovRad = 1.0f / (tan(fFov * 0.5f / 180.0f * 3.14159f));

	// setting up the projection matrix
	matProj[0][0] = fAspectRatio * fFovRad;
	matProj[1][1] = fFovRad;
	matProj[2][2] = fFar / (fFar - fNear);
	matProj[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj[2][3] = 1.0f;
	matProj[3][3] = 0.0f;
	
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
	rect.x = 0;
	rect.y = 0;
	
	// attemtping to make a 16*16 grid, which will be a terrain.
	// it will consist of 16*16 points.
	// every coordinate will be (0, 0, 0), (1, 0, 0), ... , (15, 0, 0) , (0, 0, 1), (1, 0, 1), ... , (15, 0, 15).
	// we will use the random number generation, and put number[i] into point[i].y. y will be the height of the given "node".
	vec3 pTerrain[16*16];
	
	for (int row=0; row<16; row++)
	{
		for (int col=0; col<16; col++)
		{
			pTerrain[(16*row)+col].x = col;
			pTerrain[(16*row)+col].z = row;
			pTerrain[(16*row)+col].y = (1.0f/256.0f) * random_numbers[(16*row)+col];
		}
	}
	
	// pushing the grid into a desirable position
	for (int i=0; i<16*16; i++)
	{
		pTerrain[i] = SIB_ModelTrans(pTerrain[i], modelVec);
		printf("transformed pTerrain[%d] = %f, %f, %f\n", i, pTerrain[i].x,
							pTerrain[i].y,
							pTerrain[i].z);
	}

	// offsetting the points into the screen, and scaling them into view
        for (int i=0; i<16*16; i++)
        {
                pTerrain[i].z += 3.0f;
        }

	// transforming the points with the projection matrix
	for (int i=0; i<16*16; i++)
	{
		pTerrain[i] = SIB_ProjTrans(pTerrain[i], matProj, pTerrain[i]);
	}

	// scaling the points into view
	for (int i=0; i<16*16; i++)
	{
		pTerrain[i].x += 1.0;;
		pTerrain[i].y += 1.0f;

		pTerrain[i].x *= 0.5f * (float)SCREEN_WIDTH;
		pTerrain[i].y *= 0.5f * (float)SCREEN_HEIGHT;
	}
	
	// initializing the grid's triangles
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
                        terrainBot[(15*row)+col].p1 = pTerrain[(16*row)+col+1];
                        terrainBot[(15*row)+col].p2 = pTerrain[(16*(row+1))+col+1];
                        terrainBot[(15*row)+col].p3 = pTerrain[(16*(row+1))+col];                        
                }
        }


	/*
	// print the pTerrain points	
	for (int i=0; i<256; i++)
	{
		printf("pTerrain[%d] = %f, %f, %f\n", i,  pTerrain[i].x, pTerrain[i].y, pTerrain[i].z);
	}
	*/


	// initialize engine
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
			rect.x = 0;
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

		rect.x = 0;
		rect.y = 0;
	}

	game_cleanup(&engine, EXIT_SUCCESS);	

	return 0;
}

vec3 SIB_ModelTrans(vec3 p, vec3 d)
{
	p.x += d.x;
	p.y += d.y;
	p.z += d.z;	

	return p;
}

vec3 SIB_ProjTrans      (vec3 p, float m[4][4], vec3 o)
{
	o.x = p.x*m[0][0] + p.y*m[1][0] + p.z*m[2][0] + m[3][0];
	o.y = p.x*m[0][1] + p.y*m[1][1] + p.z*m[2][1] + m[3][1];
	o.z = p.x*m[0][2] + p.y*m[1][2] + p.z*m[2][2] + m[3][2];
	float w = p.y*m[0][3] + p.y*m[1][3] + p.z*m[2][3] + m[3][3];

	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
	
	return o;	
}


// test.
