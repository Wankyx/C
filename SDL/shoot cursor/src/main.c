#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
int main(int argc, char* argv[])
{

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_bool quit = SDL_FALSE;
	SDL_Event event;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		return -1;
	}

	if(SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL can't create window and renderer : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
 
 	/*************************************************************/
	SDL_Surface* load_image = IMG_Load("resources/tank.png");
 	SDL_Texture* tank = SDL_CreateTextureFromSurface(renderer, load_image);
 	SDL_Rect tank_vector2D = {0, 0, 0, 0};

 	SDL_FreeSurface(load_image);

 	tank_vector2D.w = 64;
 	tank_vector2D.h = 64;
 	tank_vector2D.x = (800 / 2) - (64 / 2);
 	tank_vector2D.y = (600 / 2) - (64 / 2);
 
 	float angle = 180;
 	SDL_Point cursor_point = {0, 0};
 	SDL_Point cursor_tank_vector2D = {0, 0};


 	float distance = 0.0;
 	float cos_x = 0.0;
 	float sin_y = 0.0;

 	Uint32 vx = 4;
 	Uint32 vy = 4;

 	/**************************************************/

 	load_image = IMG_Load("resources/bullet.png");
 	SDL_Texture* bullet = SDL_CreateTextureFromSurface(renderer, load_image);
 	SDL_Rect bullet_vector2D = {0, 0, 0, 0};

 	SDL_FreeSurface(load_image);

 	bullet_vector2D.w = 7;
 	bullet_vector2D.h = 20;
 	bullet_vector2D.x = 50;
 	bullet_vector2D.y = 50;

 	SDL_Point bullet_point_vector2D = {0, 0};

 	SDL_bool shoot = SDL_FALSE;
 	float shoot_angle = 0.0;

 	float shoot_distance = 0.0;
 	float shoot_cos_x = 0.0;
 	float shoot_sin_y = 0.0;


 	/**************************************************/

 	Uint32 current_time = 0;
 	Uint32 last_time = 0;


 	SDL_bool first = SDL_FALSE;
 	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL; 

 	
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
  					cursor_point.x = event.motion.x;
  					cursor_point.y = event.motion.y;

  					cursor_tank_vector2D.x = cursor_point.x - tank_vector2D.x;
  					cursor_tank_vector2D.y = cursor_point.y - tank_vector2D.y;

  					angle = atan2(cursor_tank_vector2D.x, cursor_tank_vector2D.y) * 180.0 / M_PI;

  					if(angle < tank_vector2D.x)
  						angle = -angle;
  					else 
  						angle = +angle;

 					break;
				case SDL_MOUSEBUTTONDOWN:

					if(event.button.button == SDL_BUTTON_LEFT && !shoot)
					{
						shoot = SDL_TRUE;

						bullet_vector2D.x = tank_vector2D.x + 32 - 3.2;
						bullet_vector2D.y = tank_vector2D.y + 32 - 10;

			 			cursor_point.x = event.button.x;
			 			cursor_point.y = event.button.y;

			 			bullet_point_vector2D.x = cursor_point.x - bullet_vector2D.x;
			 			bullet_point_vector2D.y = cursor_point.y - bullet_vector2D.y;

			 			shoot_distance = sqrt(bullet_point_vector2D.x * bullet_point_vector2D.x + bullet_point_vector2D.y * bullet_point_vector2D.y);
			 			shoot_cos_x = bullet_point_vector2D.x / shoot_distance;
			 			shoot_sin_y = bullet_point_vector2D.y / shoot_distance;

			 			shoot_angle = angle;

					}

					break;
				case SDL_KEYDOWN:

					switch(event.key.keysym.sym)
					{
						case SDLK_z:
							distance = sqrt(cursor_tank_vector2D.x * cursor_tank_vector2D.x + cursor_tank_vector2D.y * cursor_tank_vector2D.y);
		 					cos_x = cursor_tank_vector2D.x / distance;
		 					sin_y = cursor_tank_vector2D.y / distance;
		 					tank_vector2D.x += cos_x * vx;
 							tank_vector2D.y += sin_y * vy;
							break;
					}
 				 

   					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		if(shoot)
		{
			current_time = SDL_GetTicks();

			if(current_time > 2000 + last_time)
			{
				last_time = current_time;
				shoot = SDL_FALSE;
				SDL_Log("You can shoot !\n");
			} 


			bullet_vector2D.x += shoot_cos_x * 9.81;
			bullet_vector2D.y += shoot_sin_y * 9.81;
			SDL_RenderCopyEx(renderer, bullet, NULL, &bullet_vector2D, shoot_angle, NULL, flip);
  		}




		SDL_RenderCopyEx(renderer, tank, NULL, &tank_vector2D, angle, NULL,flip);
  		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);

	}

	SDL_DestroyTexture(bullet);
 	SDL_DestroyTexture(tank);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
 