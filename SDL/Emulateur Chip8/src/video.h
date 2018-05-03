#ifndef __VIDEO__H__
#define __VIDEO__H__ 

#define WIDTH 64
#define HEIGHT 32 
#define PIXELDIM 8

#define SCREEN_W WIDTH * PIXELDIM
#define SCREEN_H HEIGHT * PIXELDIM

typedef enum 
{
	BLACK = 0,
	WHITE = 1,
	FULL = 255
}Color;

typedef struct 
{
	SDL_Rect position;
	Uint8 color;
}PIXEL;

typedef struct 
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	SDL_Texture* texture[2];
	
	PIXEL pixel[HEIGHT][WIDTH];
}VIDEO;

VIDEO video;
void CHIP8_InitVideo();
void CHIP8_InitPixel();
void CHIP8_ClearScreen();
void CHIP8_DrawPixel(const int x, const int y);
void CHIP8_UpdateScreen();

void CHIP8_QuitVideo();

#endif 
