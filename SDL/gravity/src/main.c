#include <SDL2/SDL.h>

#define SCREEN_H 408
#define SCREEN_W 408

void limit_fps(const Uint32 frame_limit);

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	
	SDL_Texture* player = NULL;
	SDL_Surface* player_image = NULL;
	SDL_Rect position = {0, 0, 0, 0};
	SDL_Rect resize = {0, 0, 0, 0};
	
	SDL_bool jstate = SDL_FALSE;
	
	Uint32 frame_limit = 0;

	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL connot init : %s\n", SDL_GetError());
		return -1;
	}
	
	if(SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL error : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	
	/*
		1000 / 60 => 16
	*/
	frame_limit = SDL_GetTicks() + 16;
	
	SDL_Log("Time %dms\n", tick);
	
	SDL_SetWindowTitle(window, "Gravity Player Jump");
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	/*******************************************************/
	
	player_image = SDL_LoadBMP("../src/player.bmp");
	
	if(player_image == NULL)
	{
		SDL_Log("SDL error : %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	
	player = SDL_CreateTextureFromSurface(renderer, player_image);
	SDL_FreeSurface(player_image);
	if(player == NULL)
	{
		SDL_Log("SDL error : %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	
	SDL_QueryTexture(player, NULL, NULL, &resize.w, &resize.h);
	position.w = 80;
	position.h = 80;
	position.y = SCREEN_H - 100;
 	SDL_RenderCopy(renderer, player, &resize, &position);
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
							position.x -= 5;
							break;
						case SDLK_RIGHT:
							position.x += 5;
							break;
						case SDLK_SPACE:
							if(jstate == SDL_FALSE)
							{
								position.y -= 60;
								jstate = SDL_TRUE;
							}
							
							break;
							
					}
					break;
				default:
					break;
			}
		}
		
		if(position.y <= SCREEN_H - 100 && jstate == SDL_TRUE)
		{
			position.y += 9,81 * 150;
		}
		else
		{
			jstate = SDL_FALSE;
		}
		 
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, player, &resize, &position);
		SDL_RenderPresent(renderer);
		SDL_Delay(60);
 	}
	
	SDL_DestroyTexture(player);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void limit_fps(const Uint32 frame_limit)
{
	Uint32 func_time = SDL_GetTicks();
	
	if(frame_limit < func_time)
		return;
	else if(frame_limit > func_time + 16)
		SDL_Delay(16);
	else 
		SDL_Delay(frame_limit - func_time);
		
	
}