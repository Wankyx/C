#include <SDL2/SDL.h>
#include "video.h"
#include "menu.h"
#include "pong.h"

int main(int argc, char* argv[])
{
	Video video = Video_Init("SDL 2.0 Pong", 800, 600);
	Player first_player;
	Player second_player;
	Ball ball;
	SDL_Color black = {0, 0, 0, 255};
	SDL_bool already_play = SDL_FALSE;
	
	StateMenu choice;
	
	Video_SetIcon(&video, "resources/icon.jpg");

	if(video.failure)
	{
		Video_Quit(&video);
		SDL_Quit();
		return -1;
	}
	
	SDL_ShowCursor(SDL_DISABLE);
	
	

  	
	while(!video.quit)
	{
		choice = Menu_Selection(&video); 	
	
		switch(choice)
		{
			case START:
				first_player = Player_Create(&video, "Player 1", 10, video.height / 2, 10, 100);
				second_player = Player_Create(&video, "Player 2", (video.width - 20)- (10/2), (video.height / 2) - (10/2), 10, 100);
				ball = Ball_Create(&video, video.width/ 2, video.height/2, 10, 10);
				
				if(first_player.failure || second_player.failure || ball.failure)
				{
					Ball_Destroy(&ball);
					Player_Destroy(&first_player);
					Player_Destroy(&second_player);
					video.quit = SDL_TRUE;
				}
				else 
				{
					video.quit = SDL_FALSE;
					already_play = SDL_TRUE;
					if(Pong_play(&video, &first_player, &second_player, &ball))
					{
						video.quit = SDL_FALSE;
					}
			 
				}
				break;
			case SCORE:
				break;
			case RULES:
				Menu_Rules(&video, 3000);
				break;
			case ABOUT:
				Menu_About(&video, 3000);
				break;
			case QUIT:
				Menu_DelayForQuit(&video, 1500);
 				break;
			case CLOSE:
				Menu_DelayForQuit(&video, 1500);
				video.quit = SDL_TRUE;
				break;
		}
	}
	
	if(already_play)
	{
		Ball_Destroy(&ball);
		Player_Destroy(&first_player);
		Player_Destroy(&second_player);
	}
 
	Video_Quit(&video);
	return 0;
}