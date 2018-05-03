#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "video.h"

Video Video_Init(const char* title, const Uint32 w, const Uint32 h)
{
	Video video;
	SDL_Color black = {0, 0, 0, 255};
	video.failure = SDL_FALSE;
	video.quit = SDL_FALSE;
	video.width = w;
	video.height = h;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL can't be init : %s\n", SDL_GetError());
		video.failure = SDL_TRUE;
		return video;
	}
	
	if(SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &video.window, &video.renderer) < 0)
	{
		SDL_Log("SDL can't create the window and renderer : %s\n", SDL_GetError());
		video.failure = SDL_TRUE;
		SDL_Quit();
		return video;
	}
	SDL_SetWindowTitle(video.window, title);
	
	Video_BackGroundColor(&video, &black);
	Video_Update(&video);
	
	return video;
}
void Video_Quit(Video* video)
{
	SDL_DestroyRenderer(video->renderer);
	SDL_DestroyWindow(video->window);
	SDL_Quit();
}

void Video_BackGroundColor(Video* video, SDL_Color* color)
{
	if(SDL_SetRenderDrawColor(video->renderer, color->r, color->g, color->b, color->a) < 0)
	{
		SDL_Log("SDL can't set render draw color : %s\n", SDL_GetError());
		video->failure = SDL_TRUE;
		return;
	}
	
	if(SDL_RenderClear(video->renderer) < 0)
	{
		SDL_Log("SDL can't clear the renderer : %s\n", SDL_GetError());
		video->failure = SDL_TRUE;
		return;
	}
}
void Video_BackgroundImage(Video* video, const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == NULL)
	{
		SDL_Log("SDL can't load image : %s\n", SDL_GetError());
		video->failure = SDL_TRUE;
		return;
	}
	
	texture = SDL_CreateTextureFromSurface(video->renderer, surface);
	
	if(texture == NULL)
	{
		SDL_Log("SDL can't create texture : %s\n", SDL_GetError());
		video->failure = SDL_TRUE;
		return;
	}
	
	SDL_RenderCopy(video->renderer, texture, NULL, NULL);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
void Video_Update(Video* video)
{
	SDL_RenderPresent(video->renderer);
}
void Video_Transparent(Video* video, SDL_Surface* surface, SDL_Color* color)
{
	if(SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, color->r, color->g, color->b, color->a)) < 0)
	{
		SDL_Log("SDL can't set color key : %s\n", SDL_GetError());
		video->failure = SDL_TRUE;
	}
}
void Video_SetIcon(Video* video, const char* path)
{
	SDL_Surface* icon = IMG_Load(path);
	SDL_Color white = {255, 255, 255, 255};
	if(icon == NULL)
	{
		SDL_Log("SDL can't load image : %s`\n", SDL_GetError());
		video->failure = SDL_TRUE;
		return;
	}
	Video_Transparent(video, icon, &white);
	SDL_SetWindowIcon(video->window, icon);
}