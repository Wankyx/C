#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

 

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL connot be init : %s\n", SDL_GetError());
		return -1;
	}
	
	
	if(SDL_CreateWindowAndRenderer(1200, 720, SDL_WINDOW_SHOWN , &window, &renderer) < 0)
	{
		SDL_Log("SDL connot be init : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	SDL_SetWindowTitle(window, "SDL 2.0 Mouvement de sprite");
	/***************************************************************/
	SDL_Surface* sprite_walk_right[10] = {NULL};
	SDL_Texture* sprite_texture[10] = {NULL}; 
	SDL_Rect player = {0, 0, 0, 0};
	
	char* sprite_name[10] = {"ressources/png/Walk (1).png", "ressources/png/Walk (2).png", "ressources/png/Walk (3).png", 
	"ressources/png/Walk (4).png", "ressources/png/Walk (5).png", "ressources/png/Walk (6).png", "ressources/png/Walk (7).png",
	"ressources/png/Walk (8).png", "ressources/png/Walk (9).png", "ressources/png/Walk (10).png"};
	
	for(Uint8 i = 0; i < 10; i++)
	{
		sprite_walk_right[i] = IMG_Load(sprite_name[i]);
		
		if(sprite_walk_right[i] == NULL)
		{
			SDL_Log("SDL connot load img : %s\n", SDL_GetError());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return -1;
		}
	}
	
	for(Uint8 i = 0; i < 10; i++)
	{
		sprite_texture[i] = SDL_CreateTextureFromSurface(renderer, sprite_walk_right[i]);
		
		if(	sprite_texture[i] == NULL)
		{
			for(Uint8 j = 0; j < i; j++)
				SDL_DestroyTexture(sprite_texture[i]);
			for(Uint8 z = 0; z < 10; z++)
				SDL_FreeSurface(sprite_walk_right[z]);
			
			SDL_Log("SDL connot create texture : %s\n", SDL_GetError());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return -1;
		}
	}
	
	for(Uint8 i = 0; i < 10; i++)
		SDL_FreeSurface(sprite_walk_right[i]);
 	
	/***************************************************************/
	Uint8 sprite_index = 0;
 
 	player.w = 128;
	player.h = 128;
	SDL_RenderCopy(renderer, sprite_texture[sprite_index], NULL, &player);
	
	/***************************************************************/
	
	Uint32 walk_speed = 5;
	SDL_bool state = SDL_FALSE;
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
						case SDLK_LEFT:
							if(sprite_index > 0)
								sprite_index--;
							
							player.x -= walk_speed;
							state = SDL_TRUE;
							break;
						case SDLK_RIGHT:
							if(sprite_index < 9)
								sprite_index++;
							else 
								sprite_index = 0;
							
							player.x += walk_speed;
							state = SDL_TRUE;

							break;
						default:
							break;
					}
				
					break;
				default:
					break;
			}
		}
		
		SDL_Log("index : %d\n", sprite_index);
		SDL_RenderClear(renderer);
		if(state)
			SDL_RenderCopy(renderer, sprite_texture[sprite_index], NULL, &player);
		else 
			SDL_RenderCopy(renderer, sprite_texture[0], NULL, &player);
		SDL_Delay(35);
		state = SDL_FALSE;
		SDL_RenderPresent(renderer);
	}
	 
	for(Uint8 i = 0; i < 10; i++)
		SDL_DestroyTexture(sprite_texture[i]);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}