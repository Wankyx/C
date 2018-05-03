#include <SDL2/SDL.h>
#include "video.h"

void CHIP8_InitVideo()
{
	if(SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &video.window, &video.renderer) < 0)
	{
		SDL_Log("@debug SDL video feature error : %s\n", SDL_GetError());
		SDL_Quit();
	}
	
	SDL_SetWindowTitle(video.window, "CHIP-8 Emulator by wankyx");
	
	video.texture[0] = SDL_CreateTexture(video.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PIXELDIM, PIXELDIM);
	video.texture[1] = SDL_CreateTexture(video.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PIXELDIM, PIXELDIM);
	
	if(video.texture[0] == NULL ||video.texture[1] == NULL)
	{
		SDL_Log("@debug SDL video feature error : %s\n", SDL_GetError());
		
		SDL_DestroyTexture(video.texture[1]);
		SDL_DestroyTexture(video.texture[0]);
		SDL_DestroyRenderer(video.renderer);
		SDL_DestroyWindow(video.window);
		SDL_Quit();
	}
	
	SDL_SetRenderTarget(video.renderer, video.texture[0]);
	SDL_SetRenderDrawColor(video.renderer, 0, 0, 0, 255);
	SDL_RenderClear(video.renderer);
	
	SDL_SetRenderTarget(video.renderer, video.texture[1]);
	SDL_SetRenderDrawColor(video.renderer, 255, 255, 255, 255);
	SDL_RenderClear(video.renderer);
	SDL_SetRenderTarget(video.renderer, NULL);
	
}
void CHIP8_InitPixel()
{
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			video.pixel[y][x].position.x = PIXELDIM * x;
			video.pixel[y][x].position.y = PIXELDIM * y;
			
			if(x%(y+1)==0) 
				video.pixel[y][x].color = BLACK;
            else 
				video.pixel[y][x].color = WHITE;
 		}
	}
}
void CHIP8_ClearScreen()
{
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			 video.pixel[y][x].color = BLACK;
		}
	}
}
void CHIP8_DrawPixel(const int x, const int y)
{
	SDL_QueryTexture(video.texture[video.pixel[y][x].color], NULL, NULL, &video.pixel[y][x].position.w, &video.pixel[y][x].position.h);
	SDL_RenderCopy(video.renderer, video.texture[video.pixel[y][x].color], NULL, &video.pixel[y][x].position);
}
void CHIP8_UpdateScreen()
{
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			CHIP8_DrawPixel(x, y); 
		}
	}
	SDL_RenderPresent(video.renderer);
}

void CHIP8_QuitVideo()
{
	SDL_DestroyTexture(video.texture[1]);
	SDL_DestroyTexture(video.texture[0]);
	SDL_DestroyRenderer(video.renderer);
	SDL_DestroyWindow(video.window);
}