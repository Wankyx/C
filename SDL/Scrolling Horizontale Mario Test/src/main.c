#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define SPRITE_MAX 6
#define STRING_ALLOC 256

 

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;


	const char* sprite_name[STRING_ALLOC] = {"resources/mario_left.gif", "resources/mario_right.gif", "resources/mario_run_left1.gif", "resources/mario_run_right1.gif", "resources/mario_run_left2.gif", "resources/mario_run_right2.gif"};
	SDL_Surface* sprite[SPRITE_MAX] = {NULL};

	Uint32 sprite_index = 0;
	Uint32 tmp_sprite_index = 0;

	SDL_Rect mario = {0, 0, 0, 0};
	SDL_Texture* mario_texture[SPRITE_MAX] = {NULL};

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		return -1;
	}


	if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL can't create window and renderer : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
	{
		sprite[sprite_index] = IMG_Load(sprite_name[sprite_index]);

		if(sprite[sprite_index] == NULL)
		{
			SDL_Log("SDL_Image Sprite can't be load : %s\n", SDL_GetError());
			tmp_sprite_index = sprite_index;
			for(sprite_index = 0; sprite_index < tmp_sprite_index; sprite_index++)
			{
				SDL_FreeSurface(sprite[sprite_index]);
			}
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return -1;
		}
	}

	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
	{
		mario_texture[sprite_index] = SDL_CreateTextureFromSurface(renderer, sprite[sprite_index]);

		if(mario_texture[sprite_index] == NULL)
		{
			SDL_Log("SDL can't create texture : %s\n", SDL_GetError());
			tmp_sprite_index = sprite_index;
			for(sprite_index = 0; sprite_index < tmp_sprite_index; sprite_index++)
			{
				SDL_DestroyTexture(mario_texture[sprite_index]);
			}
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return -1;
		}
 	}

 	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
	{
		SDL_FreeSurface(sprite[sprite_index]);
	}

	mario.w = 64;
	mario.h = 64;
  	SDL_RenderCopy(renderer, mario_texture[1], NULL, &mario);

  	/**************************************************************/
  	SDL_Rect world = {0, 0, 0, 0};
  	SDL_Surface* world_surface = IMG_Load("resources/world.png");
  	SDL_Texture* world_texture = NULL;

  	if(world_surface == NULL)
  	{
  		SDL_Log("SDL_image can't load image : %s\n", SDL_GetError());


	 	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
		{
			SDL_FreeSurface(sprite[sprite_index]);
		}

		for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
		{
			SDL_DestroyTexture(mario_texture[sprite_index]);
		}
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		SDL_Quit();
		return -1;
  	}

  	world_texture = SDL_CreateTextureFromSurface(renderer, world_surface);

  	if(world_texture == NULL)
  	{
  		SDL_Log("SDL_image can't load image : %s\n", SDL_GetError());


	 	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
		{
			SDL_FreeSurface(sprite[sprite_index]);
		}

		for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
		{
			SDL_DestroyTexture(mario_texture[sprite_index]);
		}
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		SDL_Quit();
		return -1;
  	}

  	SDL_FreeSurface(world_surface);

  	world.w = 400;
  	world.h = 400;
  	world.y = 200;
  	world.x = 0;

  	mario.x = 10;
  	mario.y = 474;
 
  	/**************************************************************/

  	Uint32 vx = 2.5;
  	Uint32 vy = 2.5;

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_RIGHT:
							if((world.x + 10) < 800) 
							{
								world.x += 10;
								mario.x += 10;

							}

							SDL_Log("world.x = %d\n", world.x);
 							break;
						case SDLK_LEFT:
							if((world.x - 10) > 0) 
							{
								world.x -= 10;
								mario.x -= 10;
							}
							SDL_Log("world.x = %d\n", world.x);
 							break;
						case SDLK_LSHIFT:
							break;
					}
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, world_texture, &world, NULL);
   		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	for(sprite_index = 0; sprite_index < SPRITE_MAX; sprite_index++)
	{
		SDL_DestroyTexture(mario_texture[sprite_index]);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}