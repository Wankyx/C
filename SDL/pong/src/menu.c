#include <SDL2/SDL.h>
#include "video.h"
#include "menu.h"

StateMenu Menu_Selection(Video* video)
{
	char* path[STRING_MEMORY_ALLOCATION] = {"resources/menu_start.bmp", "resources/menu_score.bmp", "resources/menu_rules.bmp", "resources/menu_about.bmp", "resources/menu_quit.bmp"};
	StateMenu choice = START;
	SDL_bool wm_state = SDL_FALSE;
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
						case SDLK_F11:
							if(!wm_state)
							{
								wm_state = SDL_TRUE;

								if (SDL_SetWindowFullscreen(video->window, SDL_WINDOW_FULLSCREEN) < 0)
								{
									SDL_Log("SDL can't set window to fullscreen : %s\n", SDL_GetError());
								}
								SDL_Log("quit : %d\n", video->quit);
 							}
							else 
							{
								wm_state = SDL_FALSE;
								if (SDL_SetWindowFullscreen(video->window, 0) < 0)
								{
									SDL_Log("SDL can't set window to fullscreen : %s\n", SDL_GetError());
								}
							} 							
  							break;
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