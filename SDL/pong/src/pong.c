#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <stdlib.h>
#include "math.h"
#include "video.h"
#include "pong.h"

Player Player_Create(Video* video, const char* username, const Uint32 x, const Uint32 y, const Uint32 w, const Uint32 h)
{
	Uint8 i = 0;
	Player player;
	
	player.speed = 15;
	player.position.x = x;
	player.position.y = y;
	player.position.w = w;
	player.position.h = h;
	player.score = 0;
	
	player.username = username;
	
	player.texture = SDL_CreateTexture(video->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	
	if(player.texture == NULL)
	{
		SDL_Log("SDL can't create the texture : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
		return player;
	}
	
 	if (SDL_SetRenderTarget(video->renderer, player.texture) < 0)
	{
		SDL_Log("SDL can't change render target : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
 		return player;
	}
	
	if (SDL_SetRenderDrawColor(video->renderer, 255, 255, 255, 255) < 0)
	{
		SDL_Log("SDL can't set render draw color : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
 		return player;
	}
	
	if(SDL_RenderClear(video->renderer)  < 0)
	{
		SDL_Log("SDL can't draw in the renderer : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
		return player;
	}
	
	if(SDL_SetRenderTarget(video->renderer, NULL) < 0)
	{
		SDL_Log("SDL can't change render target : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
 		return player;
	}
	
	if(SDL_RenderCopy(video->renderer, player.texture, NULL, &player.position) < 0)
	{
		SDL_Log("SDL can't load in memory the texture : %s\n", SDL_GetError());
		player.failure = SDL_TRUE;
 		return player;
	}
	
	
	return player;
	
}
void Player_Destroy(Player* player)
{
	SDL_DestroyTexture(player->texture);
}

void Player_Draw(Player* player, Video* video)
{
	if(SDL_RenderCopy(video->renderer, player->texture, NULL, &player->position) < 0)
	{
		SDL_Log("SDL can't load in memory the texture : %s\n", SDL_GetError());
		player->failure = SDL_TRUE;
 	}
}

/*******************************************************/
Ball Ball_Create(Video* video, const Uint32 x, const Uint32 y, const Uint32 w,  const Uint32 h)
{
	Ball ball;
	
	ball.angle = 0;
	ball.speed = 0;
	ball.vx = 0;
	ball.vy = 0;
	ball.position.x = x;
	ball.position.y = y;
	ball.position.w = w;
	ball.position.h = h;
	ball.failure = SDL_FALSE;
	ball.shoot = SDL_FALSE;
	
	ball.texture = SDL_CreateTexture(video->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	
	if(ball.texture == NULL)
	{	
		SDL_Log("SDL can't create the texture : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
		return ball;
	}
	
	if(SDL_SetRenderTarget(video->renderer, ball.texture) < 0)
	{
		SDL_Log("SDL can't change render target : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
		return ball;
	}
	
	if (SDL_SetRenderDrawColor(video->renderer, 255, 255, 255, 255) < 0)
	{
		SDL_Log("SDL can't set render draw color : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
 		return ball;
	}
	
	if(SDL_RenderClear(video->renderer)  < 0)
	{
		SDL_Log("SDL can't draw in the renderer : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
		return ball;
	}
	
	if(SDL_SetRenderTarget(video->renderer, NULL) < 0)
	{
		SDL_Log("SDL can't change render target : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
 		return ball;
	}
	
	if(SDL_RenderCopy(video->renderer, ball.texture, NULL, &ball.position) < 0)
	{
		SDL_Log("SDL can't load in memory the texture : %s\n", SDL_GetError());
		ball.failure = SDL_TRUE;
 		return ball;
	}
	
	return ball;
}

void Ball_Destroy(Ball* ball)
{
	SDL_DestroyTexture(ball->texture);
}

void Ball_Draw(Ball* ball, Video* video)
{
	if(SDL_RenderCopy(video->renderer, ball->texture, NULL, &ball->position) < 0)
	{
		SDL_Log("SDL can't load in memory the texture : %s\n", SDL_GetError());
		ball->failure = SDL_TRUE;
 	}
}
/********************************************************************************/

SDL_bool Pong_play(Video* video, Player* first_player, Player* second_player ,Ball* ball)
{
	
	SDL_bool return_menu = SDL_FALSE;

	Mix_Music* sound[3] = {NULL};
	const char* path[3] = {"resources/ball_hit_wall.wav", "resources/ball_hit_paddle.wav", "resources/player_miss_ball.wav"};
	Uint8 i = 0;
	
	SDL_Color black = {0, 0, 0, 255};
	SDL_bool start = SDL_TRUE;
	SDL_bool corner_up = SDL_FALSE;
	SDL_bool corner_down = SDL_FALSE;
	SDL_bool play_corner_sound = SDL_FALSE;
	
 	
	srand(time(NULL));

	if(Mix_OpenAudio(41000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		SDL_Log("Mix can't be init : %s\n", Mix_GetError());
	}
	
	for(i = 0; i < 3; i++)
	{
		sound[i] = Mix_LoadMUS(path[i]);
 
		if(sound[i] == NULL)
		{
			SDL_Log("Mix can't load audio : %s\n", Mix_GetError());
		}
	}

	
 	
 	while(!video->quit)
	{
		while(SDL_PollEvent(&video->event))
		{
			switch(video->event.type)
			{
				case SDL_QUIT:
					video->quit = SDL_TRUE;
					return_menu = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					
					switch(video->event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							video->quit = SDL_TRUE;
							return_menu = SDL_TRUE;
							break;
						case SDLK_UP:
							if(first_player->position.y > 0)
								first_player->position.y -= first_player->speed;
							break;
						case SDLK_DOWN:
							
							if(first_player->position.y + first_player->position.h < video->height)
								first_player->position.y += first_player->speed;							
							break;
					}
					
					break;
				case SDL_MOUSEMOTION:
					if(first_player->position.y < 0)
						first_player->position.y = 1;
					else if(first_player->position.y + first_player->position.h > video->height)
						first_player->position.y = video->height - first_player->position.h - 1;
					else 
						first_player->position.y = video->event.motion.y;
					break;
			}	
		}
		
		if(SDL_HasIntersection(&first_player->position, &ball->position))
		{
			start = SDL_FALSE;
			ball->shoot = SDL_TRUE;
			ball->angle = rand() % 180;
			ball->speed +=2;
 			ball->direction = rand() % 2 ;
			
 			corner_up = SDL_FALSE;
			corner_down = SDL_FALSE;
			play_corner_sound = SDL_FALSE;

			Mix_PlayMusic(sound[1], 1);  

		}
		else 
		{
			if(SDL_HasIntersection(&second_player->position, &ball->position))
			{
				start = SDL_FALSE;
				ball->shoot = SDL_FALSE;
				
 				ball->angle = rand() % 180;
				ball->speed +=2;
				ball->position.x -= ball->vx;
				ball->direction = rand() % 2;
				
 				corner_up = SDL_FALSE;
				corner_down = SDL_FALSE;
				play_corner_sound = SDL_FALSE;
				
				Mix_PlayMusic(sound[1], 1);  

			}
			else 
			{
				if(start)
				{
					ball->position.x = (video->width / 2) - (ball->position.w / 2);
					ball->position.y = (video->height / 2) - (ball->position.h / 2);
					ball->shoot = SDL_TRUE;
 					ball->angle = rand() % 180;  // RANDOM ANGLE 0 AND 180
					ball->speed = 3;
					ball->direction = rand() % 2;
					
					 
					
					first_player->position.y = video->height / 2;
					second_player->position.y = video->height / 2;

					start = SDL_FALSE;
					SDL_Delay(1000/30);
				}
			}
		}
		
		if(ball->shoot)
		{
			if(!corner_up && !corner_down)
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x += ball->vx;
				
				if(ball->direction == 0)
					ball->position.y += ball->vy;
				else 
					ball->position.y -= ball->vy;
			}
			 
		}
		else 
		{
			if(!corner_up && !corner_down)
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x -= ball->vx;
				
				if(ball->direction == 0)
					ball->position.y += ball->vy;
				else 
					ball->position.y -= ball->vy;
			}
		 
		}
		
		if(ball->position.y < 1 || corner_up)
		{
			corner_up = SDL_TRUE;
			
			if(!play_corner_sound)
			{
				Mix_PlayMusic(sound[0], 1);  
				play_corner_sound = SDL_TRUE;
			}
 
			if(ball->shoot)
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x += ball->vx;
				ball->position.y += ball->vy;
			}
			else 
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x -= ball->vx;
				ball->position.y += ball->vy;
 			}
		}
		
		if((ball->position.y+ball->position.h) > video->height || corner_down)
		{
			corner_down = SDL_TRUE;
			
			if(!play_corner_sound)
			{
				Mix_PlayMusic(sound[0], 1);
				play_corner_sound = SDL_TRUE;
			}
 
			if(ball->shoot)
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x += ball->vx;
				ball->position.y -= ball->vy;
			}
			else 
			{
				ball->vx = ball->speed * cos(ball->angle / 180 * M_PI);
				ball->vy = ball->speed * sin(ball->angle * M_PI / 180);
				ball->position.x -= ball->vx;
				ball->position.y -= ball->vy;
 			}
		}
		
		if(ball->shoot && ball->position.x > second_player->position.x)
		{
			Mix_PlayMusic(sound[2], 1);  

			first_player->score ++;
			start = SDL_TRUE;
		}
		else 
		{
			if(!ball->shoot && ball->position.x < first_player->position.x)
			{
				Mix_PlayMusic(sound[2], 1);  

				second_player->score++;
				start = SDL_TRUE;
			}
		}
		
		if(ball->shoot)
		{
			if(second_player->position.y > -1 && (second_player->position.y + second_player->position.h) < video->height)
			{
				if(ball->position.y > (second_player->position.y + (second_player->position.h / 2)))
				{
					second_player->position.y += second_player->speed;
				}
				else if(ball->position.y < (second_player->position.y + (second_player->position.h / 2)))
				{
					second_player->position.y -= second_player->speed;
				}
			}
			else 
			{
				if(second_player->position.y < 0)
					second_player->position.y = 0;
				else 
					if((second_player->position.y + second_player->position.h) > video->height)
						second_player->position.y = video->height - second_player->position.h - 1;

			}
			 
		}
		/*
		if(!ball->shoot)
		{
			if(ball->position.y > (first_player->position.y + (first_player->position.h / 2)))
			{
				first_player->position.y += first_player->speed;
			}
			else if(ball->position.y < (first_player->position.y + (first_player->position.h / 2)))
			{
				first_player->position.y -= first_player->speed;
			}
		}
		*/
 		Video_BackGroundColor(video, &black);
		Ball_Draw(ball, video);
		Player_Draw(first_player, video);
		Player_Draw(second_player, video);
		Video_Update(video);
		SDL_Delay(1000/30);
		 
 	}
	
	for(i = 0; i < 3; i++)
	{
		Mix_FreeMusic(sound[i]);
	}
	
	Mix_CloseAudio();
	
	return return_menu;
}
 
 