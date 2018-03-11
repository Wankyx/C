#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TILES 30

int main(int argc, char** argv)
{
    /*********************************************************/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Uint32 width = 900;
	Uint32 height = 600;
	Uint8 title[256] = {"[SDL 2] ... The Snake Game ..."};
	SDL_Color wcolor = {127, 128, 127, 255}; 
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		SDL_Log("SDL_Init failure : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	if(SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL_CreateWindowAndRenderer failure : %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}
	srand(time(NULL));
	SDL_SetWindowTitle(window, title);
	SDL_SetRenderDrawColor(renderer, wcolor.r, wcolor.g, wcolor.b, wcolor.a);
	SDL_RenderClear(renderer);
 
    
    /*********************************************************/
	Uint32 length = 0;
	Uint32 tiles = 0;
	Uint32 vx = 25;
	Uint32 vy = 25;

	Uint32 patch_velocity = 25;

	Uint32 prev_x[TILES] = {0};
	Uint32 prev_y[TILES] = {0};

 

	SDL_Color head = {0, 255, 0, 255};
	SDL_Color body = {0, 0, 255, 255};

	/*		index				0	  1		2		3	
			SDL_bool key[4] = {HAUT, BAS, DROITE, GAUCHE}
	*/
	SDL_bool key[4] = {SDL_FALSE, SDL_FALSE, SDL_TRUE, SDL_FALSE};

	SDL_Texture* snake_texture[TILES];
	SDL_Rect snake_body[TILES];

	for(length = 0; length < TILES; length++)
	{
		snake_texture[length] = NULL;
		snake_body[length].x = 0, snake_body[length].y = 0;
		snake_body[length].w = 0,  snake_body[length].h = 0;
	}
	length = 0;

		// La taille length = 0 est la tête donc l'index 0 est la tête sur le snake_texture et le snake_body
	snake_texture[length] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 25, 25);

	SDL_SetRenderTarget(renderer, snake_texture[length]);
	SDL_SetRenderDrawColor(renderer, head.r, head.g, head.b, head.a);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	snake_body[length].x = 50; // La tête commence au coordonnées (30;30);
	snake_body[length].y = 50;
	SDL_QueryTexture(snake_texture[length], NULL, NULL, &snake_body[length].w, &snake_body[length].h);
	SDL_RenderCopy(renderer, snake_texture[length], NULL, &snake_body[length]);

	SDL_RenderPresent(renderer);
 
	/***********************************************************/
	SDL_Rect meat = {0, 0, 0, 0};
	SDL_Color meat_color = {63, 63, 63, 255};
	SDL_Texture* meat_texture = NULL;

	meat_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 25, 25);
 	
 	SDL_SetRenderTarget(renderer, meat_texture);
 	SDL_SetRenderDrawColor(renderer, meat_color.r, meat_color.g, meat_color.b, meat_color.a);
 	SDL_RenderClear(renderer);
 	SDL_SetRenderTarget(renderer, NULL);

 	SDL_QueryTexture(meat_texture, NULL, NULL, &meat.w, &meat.h);
 	meat.x = 30;
 	meat.y = 400;
 	SDL_RenderCopy(renderer, meat_texture, NULL, &meat);
 	SDL_RenderPresent(renderer);

	/***********************************************************/

	SDL_Event event;
	SDL_bool close = SDL_FALSE;

	while(!close || length == 30)
	{
		SDL_PollEvent(&event);
		SDL_Delay(100);

		switch(event.type)
		{
			case SDL_QUIT:
				close = SDL_TRUE;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					close = SDL_TRUE;
				else 
				{
					if(event.key.keysym.sym == SDLK_SPACE)
						getchar();

					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							if(key[1] == SDL_FALSE)
							{
								key[0] = SDL_TRUE;
								key[1] = SDL_FALSE;
								key[2] = SDL_FALSE;
								key[3] = SDL_FALSE;
							}
						 
							break;
						case SDLK_DOWN:
							if(key[0] == SDL_FALSE)
							{
								key[0] = SDL_FALSE;
								key[1] = SDL_TRUE;
								key[2] = SDL_FALSE;
								key[3] = SDL_FALSE;
							}
					 
							break;
						case SDLK_RIGHT:
							if(key[3] == SDL_FALSE)
							{
								key[0] = SDL_FALSE;
								key[1] = SDL_FALSE;
								key[2] = SDL_TRUE;
								key[3] = SDL_FALSE;
							}

							break;
						case SDLK_LEFT:
							if(key[2] == SDL_FALSE)
							{
								key[0] = SDL_FALSE;
								key[1] = SDL_FALSE;
								key[2] = SDL_FALSE;
								key[3] = SDL_TRUE;	
							}	
						 						
							break;
					}
				}
				break;
		}
 		if( (snake_body[0].x + snake_body[0].w) > width)
		{
			close = SDL_TRUE;
		}
		else if ( (snake_body[0].y + snake_body[0].h) > height) 
		{
			close = SDL_TRUE;
		}
		else if (snake_body[0].x < 0 || snake_body[0].y < 0)
		{
			close = SDL_TRUE;
		}


		if(key[0] == SDL_TRUE )
			snake_body[0].y -= vy;
		else if(key[1] == SDL_TRUE)
			snake_body[0].y += vy;
		else if(key[2] == SDL_TRUE)
			snake_body[0].x += vx;
		else 
			snake_body[0].x -= vx;

		if(SDL_HasIntersection(&snake_body[0], &meat))
		{
			meat.x = (10+ rand()) % (width - 10);
 			meat.y = (10+ rand()) % (height - 10);
			++length;
			snake_texture[length] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 25, 25);
			SDL_SetRenderTarget(renderer, snake_texture[length]);
			SDL_SetRenderDrawColor(renderer, body.r, body.g, body.b, body.a);
			SDL_RenderClear(renderer);
			SDL_SetRenderTarget(renderer, NULL);
			SDL_QueryTexture(snake_texture[length], NULL, NULL, &snake_body[length].w, &snake_body[length].h); 		 
			SDL_RenderPresent(renderer);

			SDL_Log("Length of the snake is : %d\n", length);
		 
 		}
 		else 
 		{
 			for(tiles = 0; tiles <= length; tiles++)
 			{
 				if(SDL_HasIntersection(&snake_body[0], &snake_body[tiles]) && tiles > 0)
 				{
 					SDL_Log("You Win");
					close = SDL_TRUE;
 				}
 			}
 		}

 		if(length == TILES)
		{	
			SDL_Log("You Win");
			close = SDL_TRUE;
  		}
		else 
		{

	 		for(tiles = 0; tiles <= length; tiles++)
	 		{
	 			prev_x[tiles] = snake_body[tiles].x;
	 			prev_y[tiles] = snake_body[tiles].y;
	 		}

			SDL_SetRenderDrawColor(renderer, wcolor.r, wcolor.g, wcolor.b, wcolor.a);
			SDL_RenderClear(renderer);
	 		SDL_RenderCopy(renderer, meat_texture, NULL, &meat);
	 
	  		for(tiles = 0; tiles <= length; tiles++)
	 		{
	 			if(tiles > 0)
	 			{
	 				if(tiles == 1)
	 				{ 					
		 				if(key[0] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1] + patch_velocity;
		 				}
		 				else if (key[1] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1] - patch_velocity;
		 				}
		 				else if (key[2] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1] - patch_velocity;
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 				else 
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1] + patch_velocity;
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 			}
		 			else 
		 			{
		 				if(key[0] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 				else if (key[1] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 				else if (key[2] == SDL_TRUE)
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 				else 
		 				{
		 					snake_body[tiles].x = prev_x[tiles-1];
		 					snake_body[tiles].y = prev_y[tiles-1];
		 				}
		 			}
	 			} 
	 		 
				SDL_RenderCopy(renderer, snake_texture[tiles], NULL, &snake_body[tiles]);
	 		}
	 	}
		SDL_RenderPresent(renderer); 
	}

 	/***********************************************************/
	/* Libération mémoire */
	length = 0;
	for(length = 0; length < TILES; length++)
	{
		SDL_DestroyTexture(snake_texture[length]);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
    return EXIT_SUCCESS;
}
