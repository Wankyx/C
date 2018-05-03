#include <SDL2/SDL.h>
#include "video.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main(int argc, char* argv[])
{
	VideoModule* video = VideoModule_Init();
	const char* path = VideoModule_PathImage();
	
 	if(VideoModule_LoadImage(video, path)) 
	{
		return EXIT_FAILURE;
	}
	VideoModule_SeparateOneByOneOnSurface(video);
	
	VideoModule_Quit(video);
	return EXIT_SUCCESS;
}