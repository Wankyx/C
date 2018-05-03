#ifndef __PONG__H__ 
#define __PONG__H__ 

#ifndef DEBUG_LOG 

#define debug_line(); SDL_Log("LINE : %d", __LINE__);

#endif 

#define STRING_MEMORY_ALLOCATION 256

typedef struct 
{	
	Uint32 speed;
	SDL_Rect position;
	SDL_Texture* texture;
	Uint32 score;
	const char* username;
	SDL_bool failure;
}Player;

typedef struct 
{
	Uint32 angle;
	Uint32 vx;
	Uint32 vy;
	Uint32 speed;
	Uint32 direction;
	SDL_Rect position;
	SDL_Texture* texture; 
	
	SDL_bool shoot;
	SDL_bool failure;
}Ball;

 

Player Player_Create(Video* video, const char* username, const Uint32 x, const Uint32 y, const Uint32 w, const Uint32 h);
void Player_Destroy(Player* player);
void Player_Draw(Player* player, Video* video);

 
/*******************************************************/
Ball Ball_Create(Video* video, const Uint32 x, const Uint32 y, const Uint32 w,  const Uint32 h);
void Ball_Draw(Ball* ball, Video* video);
void Ball_Destroy(Ball* ball);
/*******************************************************/
SDL_bool Pong_play(Video* video, Player* player, Player* second_player, Ball* ball);

/*******************************************************/
 

#endif 