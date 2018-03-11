#include <SDL2/SDL.h>
#include <math.h>

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Event event;
	SDL_bool quit = SDL_FALSE;


	SDL_Texture* texture = NULL;
	SDL_Rect geometric_shape = {200, 200, 0, 0};


	/******************************************************************/
	float distance = 0.0;
	float x = 0.0;
	float y = 0.0;

	float cos_x = 0.0f;
	float sin_y = 0.0f;

	float vx = 2.5;
	float vy = 2.5;


	/******************************************************************/

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		return -1;
	}

	if(SDL_CreateWindowAndRenderer(400, 400, SDL_WINDOW_SHOWN, &window, &renderer) < 0)
	{
		SDL_Log("SDL can't create window and renderer : %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	
	SDL_SetWindowTitle(window, "SDL trigonometrie suivre le curseur");

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);


	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 20, 20);

	if(texture == NULL)
	{
		SDL_Log("SDL can't create texture : %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);

	SDL_QueryTexture(texture, NULL, NULL, &geometric_shape.w, &geometric_shape.h);
	SDL_RenderCopy(renderer, texture, NULL, &geometric_shape);



	while(!quit)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				quit = SDL_TRUE;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					x = event.button.x - geometric_shape.x;
					y = event.button.y - geometric_shape.y; 
					distance = sqrt(pow(x, 2) + pow(y, 2));
					

					cos_x = x / distance;
					sin_y = y / distance;
 
					SDL_Log("======================================================\n");
					SDL_Log("=\t(x = %.2f, y = %.2f)\n", x, y);
					SDL_Log("=\t|z| = %.2f\n", distance);
					SDL_Log("======================================================\n");
				}
				break;
		}


		geometric_shape.x += cos_x * vx;
		geometric_shape.y += sin_y * vy;

		if(geometric_shape.x == event.button.x && geometric_shape.y == event.button.y)
		{
			SDL_Log("STOP\n");

			geometric_shape.x = 200;
			geometric_shape.y = 200;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, &geometric_shape);
		SDL_RenderPresent(renderer);
	}

 	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}