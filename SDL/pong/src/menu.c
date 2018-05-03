#include <SDL2/SDL.h>
#include "video.h"
#include "menu.h"

StateMenu Menu_Selection(Video* video)
{
	char* path[STRING_MEMORY_ALLOCATION] = {"resources/menu_start.bmp", "resources/menu_score.bmp", "resources/menu_rules.bmp", "resources/menu_about.bmp", "resources/menu_quit.bmp"};
	StateMenu choice = START;
	
	while(!video->quit)
	{
		while(SDL_PollEvent(&video->event))
		{
			switch(video->event.type)
			{
				case SDL_QUIT:
					return CLOSE;
					break;
				case SDL_KEYDOWN:
					switch(video->event.key.keysym.sym)
					{
						case SDLK_UP:
							
							if(choice > START)
								choice --;
									
							break;
						case SDLK_DOWN:
							if(choice < QUIT)
								choice++;
							break;
						case SDLK_RETURN:
							video->quit = SDL_TRUE;
					}
				default:
					break;
			}
			Video_BackgroundImage(video, path[choice]);
			Video_Update(video);

  		}
 		SDL_Delay(16);
	}
 	return choice;
}

void Menu_Rules(Video* video, Uint32 time)
{
	Video_BackgroundImage(video, "resources/rules.bmp");
	Video_Update(video);
	SDL_Delay(time);
	video->quit = SDL_FALSE;

}

void Menu_DelayForQuit(Video* video, Uint32 time)
{
	Video_BackgroundImage(video, "resources/end.bmp");
	Video_Update(video);
	SDL_Delay(time);
}
void Menu_About(Video* video, Uint32 time)
{
	Video_BackgroundImage(video, "resources/about.bmp");
	Video_Update(video);
	SDL_Delay(time);
	video->quit = SDL_FALSE;
}