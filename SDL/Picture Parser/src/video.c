#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "video.h"

SDL_bool VideoModule_SurfaceLoaded = SDL_FALSE;
 SDL_bool VideoModule_SurfaceArrayAllocated = SDL_FALSE;

static void empty_buffer_IO(void)
{
	char buffer = 0;
	do
	{
		buffer = getchar(); 
	}while(buffer != '\n' && buffer != EOF);
}

static Uint32 input_Uint32(const char* msg)
{
	Uint32 number = 0;

	printf(msg);
 	while(number <= 0)
	{
		while(scanf("%d", &number) != 1);
	}
	empty_buffer_IO();
	return number;
}

static Uint32 resolution_choice(const Uint32 nresolution)
{
	Uint32 choice = 0;
	printf("[+] What do you choice for screen resolution >> ");
	while(scanf("%d", &choice) != 1)
		empty_buffer_IO();

	if(choice < 0 || choice > nresolution-1)
		return resolution_choice(nresolution);
	
	empty_buffer_IO();
	return choice;
}

const char* path_image()
{
	static char buffer[STRING_LENGTH];
	memset(buffer, '\0', STRING_LENGTH-1);
	
	printf("[+] Please enter the path of image >> ");
	fgets(buffer, STRING_LENGTH-1, stdin);
	empty_buffer_IO();
	
	return buffer;
}
static void change_buffer_enter(char buffer[STRING_LENGTH])
{
	char* _char = strchr(buffer, '\n');
	
	if(_char != NULL)
		*_char = '\0';
	
}

/**********************************************/
VideoModule* VideoModule_Init()
{
 	VideoModule* video = malloc(sizeof(*video));
 	VideoModule_SurfaceLoaded = SDL_FALSE;

	SDL_DisplayMode display_mode;
	
	Uint32 choice = 0;
	Uint32 error = 0;
	Uint32 i = 0;
 	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL connot be init : %s\n", SDL_GetError());
		VideoModule_Quit(video);
		return NULL;
	}
	
	
	if(video == NULL)
	{
		fprintf(stderr, "[VIDEO_MODULE] Error to allocated the memory.\n");
		perror("Detected");
		VideoModule_Quit(video);
 		return NULL;
	}
	 
	choice = resolution_choice(VideoModule_ShowDisplays());
	
	if(SDL_GetDisplayMode(0, choice, &display_mode) != 0)
	{
		SDL_Log("SDL error can't get display mode selected : %s\n", SDL_GetError());
		VideoModule_Quit(video);
 		return NULL;
	}
	video->allocated_memory = 0;
	video->w = display_mode.w;
	video->h = display_mode.h;
	video->refresh = display_mode.refresh_rate;
 	video->surface = NULL;
	video->texture = NULL;
	
	for(i = 0; i < ARRAY_TO_ALLOCATED; i++)
	{
 		video->surface_image[i] = NULL;
	}

	video->event = malloc(sizeof(*video->event));
	
	if(video->event == NULL)
	{
		fprintf(stderr, "[VIDEO_MODULE] Error to allocated the memory.\n");
		perror("Detected");
		VideoModule_Quit(video);
		return NULL;
	}
	
	if(SDL_CreateWindowAndRenderer(video->w, video->h, SDL_WINDOW_SHOWN, &video->window, &video->renderer) < 0)
	{
		SDL_Log("SDL can't create window and renderer : %s\n", SDL_GetError());
		VideoModule_Quit(video);
		return NULL;
	}
	

	return video;
}
 

Uint32 VideoModule_ShowDisplays(void)
{
 	
	SDL_DisplayMode current_display_mode;
	Uint32 display_possibility = SDL_GetNumDisplayModes(0);
 	Uint32 i = 0;
	Uint32 selection = 0;
	Uint32 error = 0;
	
	for(i = 0; i <  display_possibility; i++, selection++)
	{
		error = SDL_GetDisplayMode(0, i, &current_display_mode);
		
		if(error != 0)
		{
			SDL_Log("SDL can't display the resolution of index #%d#\n", i);
			selection--;
		}
		else 
		{
			printf("(%d) %dx%d px %d Hz\n", selection, current_display_mode.w, current_display_mode.h, current_display_mode.refresh_rate);
		}
	}
 	return selection;
}

void VideoModule_Quit(VideoModule* data)
{
	Uint32 i = 0;

	
	if(VideoModule_SurfaceArrayAllocated)
	{
		 
		for(i = 0; i <= data->allocated_memory; i++)
		{
			SDL_FreeSurface(data->surface_image[i]);
		}
		SDL_FreeSurface(data->surface);
	 
	}
 
	SDL_DestroyWindow(data->window);
	SDL_DestroyRenderer(data->renderer);
	free(data->event);
	free(data);
	
	SDL_Quit();
}


SDL_bool VideoModule_LoadImage(VideoModule* video, const char* path)
{
	video->surface = IMG_Load(path);
	
	if(video->surface == NULL)
	{
		SDL_Log("SDL can't load image : %s\n", SDL_GetError());
		VideoModule_Quit(video);
 		return SDL_TRUE;
	}	
	VideoModule_SurfaceLoaded = SDL_TRUE;
	
	video->texture = SDL_CreateTextureFromSurface(video->renderer, video->surface);
	
	SDL_RenderCopy(video->renderer, video->texture, NULL, NULL);
	SDL_RenderPresent(video->renderer);
	
	return SDL_FALSE;
}

const char* VideoModule_PathImage()
{
	static char buffer[STRING_LENGTH];
	memset(buffer, '\0', STRING_LENGTH-1);
	
	printf("[+] Please enter the path of image >> ");
	fgets(buffer, STRING_LENGTH-1, stdin);
	
	change_buffer_enter(buffer);	
	return buffer;
}
 
void VideoModule_SeparateOneByOneOnSurface(VideoModule* video)
{
	SDL_Rect position_sprite = {0, 0, 0, 0};
	SDL_Rect position_save = {0, 0, 0, 0};
	Uint32 i = 0;
	Uint32 j = 0;

	Uint32 width_for_one = 0;
	Uint32 height_for_one = 0;

	
	Uint32 number_of_sprite_w = input_Uint32("[+] Number of sprite (W) >> ");
	Uint32 number_of_sprite_h = input_Uint32("[+] Number of sprite (H) >> ");
	
 	position_sprite.x = 0;
	position_sprite.y = 0;
	position_sprite.w = video->surface->w / number_of_sprite_w;
	position_sprite.h = video->surface->h / number_of_sprite_h;
	
	position_save.x = 0;
	position_save.y = 0;
	position_save.w = position_sprite.w;
	position_save.h = position_sprite.h;
	
	
	char path[STRING_LENGTH] = {'\0'};
	
	Uint32 count = 0;
	
	
	for(j = 0; j < (number_of_sprite_w + number_of_sprite_h); j++)
	{
		video->surface_image[j] = SDL_CreateRGBSurface(0, position_save.w, position_save.h, 32, 0, 0, 0, 0);
		video->allocated_memory = j;

		if(video->surface_image[j] == NULL)
		{
			SDL_Log("SDL can't create RGB surface : %s\n", SDL_GetError());
			VideoModule_Quit(video);
			return;
		}
		sprintf(path, "%d.bmp", j);
		
		SDL_BlitSurface(video->surface, &position_sprite, video->surface_image[j], &position_save);
		SDL_SaveBMP(video->surface_image[j], path);
		
		count++;
		
		if(count == number_of_sprite_w-1)
		{
			count = 0;
			position_sprite.y += position_save.h;
			position_sprite.x = 0;
		}
		position_sprite.x += position_save.w;
	}	 
}
 