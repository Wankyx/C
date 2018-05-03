#include <SDL2/SDL.h>
#include "cpu.h"
#include "video.h"

#define CPU_SPEEC 4
#define FPS 16

int main(int argc, char* argv[])
{
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		return -1;
	}
	
	CHIP8_InitCpu();
	CHIP8_InitVideo();
	
	CHIP8_InitPixel();
 		 
	
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
					quit = SDL_TRUE;
					break;
				default:
					break;
			}
		}
		SDL_Delay(FPS);
		CHIP8_UpdateScreen();
	}
	
	CHIP8_QuitVideo();
	SDL_Quit();
	return 0;
}