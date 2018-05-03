#ifndef __VIDEO__H__
#define __VIDEO__H__

#ifndef DEBUG_LOG 

#define debug_line(); SDL_Log("LINE : %d", __LINE__);

#endif 

typedef struct   
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	
	Uint32 width;
	Uint32 height;
	
	SDL_bool quit;
	SDL_bool failure;
}Video;

Video Video_Init(const char* title, const Uint32 w, const Uint32 h);
void Video_Quit(Video* video);

void Video_Transparent(Video* video, SDL_Surface* surface, SDL_Color* color);
void Video_SetIcon(Video* video, const char* path);
void Video_BackGroundColor(Video* video, SDL_Color* color);
void Video_BackgroundImage(Video* video, const char* path);
void Video_Update(Video* video);




#endif 