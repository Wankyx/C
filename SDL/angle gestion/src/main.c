#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdio.h>

#define WINDOW_WIDTH 300
#define WINDOW_HIGHT 300
#define STR_ALLOC 256

/*
	TTF_Init() < 0
	TTF_Quit();

	TTF_OpenFont(path, size)
	TTF_CloseFont(font)

	TTF_Font* font = TTF_OpenFont(path, size)

*/


int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;

	/************************************************************/

	SDL_Surface* load_image = NULL;

	SDL_Texture* ball_texture = NULL;
	SDL_Rect ball_center = {0, 0, 0, 0};

	SDL_Texture* ball_cursor_texture = NULL;
	SDL_Rect ball_cursor = {0, 0, 0, 0};

	/************************************************************/

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		return -1;
	}

	if(TTF_Init() < 0)
	{
		SDL_Log("TTF can't be init : %s\n", SDL_GetError());
		return -1;
	}

	if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL can't be create window and renderer : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	/*********************************************************/

	load_image = IMG_Load("resources/ball_blue.png");

	if(load_image == NULL)
	{
		SDL_Log("SDL can't load image : %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
 	ball_texture = SDL_CreateTextureFromSurface(renderer, load_image);
	if(ball_texture == NULL)
	{
		SDL_Log("SDL can't create texture : %s\n", SDL_GetError());
		SDL_FreeSurface(load_image);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_QueryTexture(ball_texture, NULL, NULL, &ball_center.w, &ball_center.h);
 	ball_center.x = (WINDOW_WIDTH / 2) - (32 / 2);
 	ball_center.y = (WINDOW_HIGHT / 2) - (32 / 2);
 	ball_center.w = 32;
 	ball_center.h = 32;
	SDL_RenderCopy(renderer, ball_texture, NULL, &ball_center);

	SDL_FreeSurface(load_image);

	load_image = IMG_Load("resources/ball_red.png");

	if(load_image == NULL)
	{
		SDL_Log("SDL can't load image : %s\n", SDL_GetError());
		SDL_DestroyTexture(ball_texture);
 		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	ball_cursor_texture = SDL_CreateTextureFromSurface(renderer, load_image);
	if(ball_cursor_texture == NULL)
	{
		SDL_Log("SDL can't create texture : %s\n", SDL_GetError());
		SDL_FreeSurface(load_image);
		SDL_DestroyTexture(ball_texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	 ball_cursor_texture = SDL_CreateTextureFromSurface(renderer, load_image);
	 SDL_QueryTexture(ball_cursor_texture, NULL, NULL, &ball_cursor.w, &ball_cursor.h);
	 ball_cursor.x = 0;
	 ball_cursor.x = 0;
	 ball_cursor.w = 32;
	 ball_cursor.h = 32;
	 SDL_RenderCopy(renderer, ball_cursor_texture, NULL, &ball_cursor);
	 SDL_FreeSurface(load_image);

	/*********************************************************/
	TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts/arial.ttf", 22);

	if(font == NULL)
	{
		SDL_Log("SDL can't load ttf : %s\n", SDL_GetError());
		SDL_FreeSurface(load_image);
		SDL_DestroyTexture(ball_texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
		return -1;
	}

	
	SDL_Color white = {255, 255, 255, 255};

	SDL_Surface* module_z = TTF_RenderUTF8_Solid(font, "|z| = ", white);

	SDL_Texture* distance_texture_text = SDL_CreateTextureFromSurface(renderer, module_z);
	SDL_Rect distance_position = {0, 0, 0, 0};
 	SDL_QueryTexture(distance_texture_text, NULL, NULL, &distance_position.w, &distance_position.h);
	SDL_RenderCopy(renderer, distance_texture_text, NULL, &distance_position);

	SDL_Surface* sangle = TTF_RenderUTF8_Solid(font, "Angle = ", white);
	SDL_Texture* angle_texture_text = SDL_CreateTextureFromSurface(renderer, sangle);
	SDL_Rect angle_position = {0, 50, 0, 0};
 	SDL_QueryTexture(angle_texture_text, NULL, NULL, &angle_position.w, &angle_position.h);
 	SDL_RenderCopy(renderer, angle_texture_text, NULL, &angle_position);


	/**********************************************************/
	char text_distance[STR_ALLOC] = {'\0'};
	char text_angle[STR_ALLOC] = {'\0'};

	Uint32 distance = 0;
	Uint32 x = 0;
	Uint32 y = 0;

	float cos_x = 0;
	float sin_y = 0;

	float angle = 0;

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				case SDL_MOUSEMOTION:
					SDL_FreeSurface(module_z);
					SDL_DestroyTexture(distance_texture_text);
					SDL_FreeSurface(sangle);
					SDL_DestroyTexture(angle_texture_text);

					ball_cursor.x = event.motion.x;
					ball_cursor.y = event.motion.y;

					x = ball_cursor.x - ball_center.x;
					y = ball_cursor.y - ball_center.y;

					distance = sqrt(x*x + y*y);
 				 	
 				 	cos_x = x / distance;
 				 	sin_y = y / distance;

 					angle = atan(x / y);
 					angle = (angle / 180) * M_PI;

					sprintf(text_distance, "|z| = %d", distance);
					sprintf(text_angle, "Angle = %f°", angle);


					module_z = TTF_RenderUTF8_Solid(font, text_distance, white);
					distance_texture_text = SDL_CreateTextureFromSurface(renderer, module_z);
 					SDL_QueryTexture(distance_texture_text, NULL, NULL, &distance_position.w, &distance_position.h);

					sangle = TTF_RenderUTF8_Solid(font, text_angle, white);
 					angle_texture_text = SDL_CreateTextureFromSurface(renderer, sangle);


					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, angle_texture_text, NULL, &angle_position);
		SDL_RenderCopy(renderer, distance_texture_text, NULL, &distance_position);
 		SDL_RenderCopy(renderer, ball_cursor_texture, NULL, &ball_cursor);
		SDL_RenderCopy(renderer, ball_texture, NULL, &ball_center);
		SDL_RenderPresent(renderer);
	}


	SDL_FreeSurface(module_z);
	SDL_DestroyTexture(distance_texture_text);

	SDL_DestroyTexture(ball_texture);
	SDL_DestroyTexture(ball_cursor_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}