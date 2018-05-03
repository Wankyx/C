#ifndef __MENU__H__ 
#define __MENU__H__ 

#ifndef DEBUG_LOG 

#define debug_line(); SDL_Log("LINE : %d", __LINE__);

#endif 

#define STRING_MEMORY_ALLOCATION 256

typedef enum 
{
	START,
	SCORE,
	RULES,
	ABOUT,
	QUIT,
	CLOSE
}StateMenu;


typedef struct 
{
	StateMenu choice;
}Menu;


StateMenu Menu_Selection(Video* video);
void Menu_Rules(Video* video, Uint32 time);
void Menu_About(Video* video, Uint32 time);
void Menu_DelayForQuit(Video* video, Uint32 time);

#endif