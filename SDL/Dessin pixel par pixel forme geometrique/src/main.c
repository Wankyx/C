#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
 
typedef struct Point
{
	int x;
	int y;
}Point;
typedef struct Rectangle
{
	int x;
	int y;
	int w;
	int h;
}Rectangle;

void draw_rectangle(Rectangle rectangle, SDL_Color color, SDL_Renderer* renderer)
{
 	Point pixel = {0, 0};
 	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for(pixel.y = rectangle.y; pixel.y < rectangle.h; pixel.y++)
	{
		for(pixel.x = rectangle.x; pixel.x < rectangle.w; pixel.x++)
		{
			SDL_RenderDrawPoint(renderer, pixel.x, pixel.y);
		}
	}
	SDL_RenderPresent(renderer);
}

 
 
int main(void)
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Color window_color = {0, 0, 0, 255};
    SDL_Color fig_color = {255, 0, 0, 255};

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
    	SDL_Log("SDL_Init > %s\n", SDL_GetError());
    	return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL 2.0 Forme geométrique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);


    if(window == NULL)
    {
    	SDL_Log("SDL_CreateWindow > %s\n", SDL_GetError());
    	SDL_Quit();
    	return EXIT_FAILURE;
    }
    else 
    {
    	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    	if(renderer == NULL)
    	{
    		SDL_Log("SDL_CreateRenderer > %s\n", SDL_GetError());
    		SDL_DestroyWindow(window);
    		SDL_Quit();
    		return EXIT_FAILURE;
    	}
    }

    SDL_SetRenderDrawColor(renderer, window_color.r, window_color.g, window_color.b, window_color.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  
    Rectangle r;
    r.x = 0;
    r.y = 0;
    r.w = 200;
    r.h = 200;
    draw_rectangle(r, fig_color, renderer);
 
  
    SDL_Delay(3000);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
