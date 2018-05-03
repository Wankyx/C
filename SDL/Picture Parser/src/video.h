#ifndef __VIDEO__H__ 
#define __VIDEO__H__ 

#define STRING_LENGTH 256

#define ARRAY_TO_ALLOCATED 1024

extern SDL_bool VideoModule_SurfaceLoaded;
extern SDL_bool VideoModule_SurfaceArrayAllocated;

typedef struct VideoModule 
{
	SDL_Window* window;
	Uint32 w;
	Uint32 h; 
	Uint32 refresh;
	
	
	
	SDL_Event* event;
	SDL_Renderer* renderer;
	
	SDL_Surface* surface;
	SDL_Texture* texture;
	
	SDL_Surface* surface_image[ARRAY_TO_ALLOCATED];
 	
	Uint32 allocated_memory;
	
}VideoModule;

static void empty_buffer_IO(void);
static void change_buffer_enter(char buffer[STRING_LENGTH]);
static Uint32 resolution_choice(const Uint32 nresolution);
static Uint32 input_Uint32(const char* msg);

 
VideoModule* VideoModule_Init();
Uint32 VideoModule_ShowDisplays(void);

SDL_bool VideoModule_LoadImage(VideoModule* video, const char* path);
void VideoModule_SeparateOneByOneOnSurface(VideoModule* video);
void VideoModule_Quit(VideoModule* data);
const char* VideoModule_PathImage();
 


#endif 