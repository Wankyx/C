#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL.h>


int main(void)
{
    SDL_Surface* screen = NULL;
    SDL_Event event;
    _Bool closed = false;
    _Bool direction = false;
    SDL_Rect clic = {0, 0, 0, 0};


    SDL_Surface* ball = NULL;
    SDL_Rect ball_position;


    float module_z = 0;
    float cos_deta = 0;
    float sin_deta=  0;
    float coefficient_directeur = 0;

    float velocity_x = 1.25;
    float velocity_y = 1.25;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
    	fprintf(stderr, "%s\n", SDL_GetError());
    	return EXIT_FAILURE;
    }


    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(screen == NULL)
    {
		fprintf(stderr, "%s\n", SDL_GetError());

    	SDL_Quit();
    	return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Trigonométrie & Informatique", NULL);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));


    /**********************************************************************/
    ball = SDL_CreateRGBSurface(SDL_HWSURFACE, 15, 15, 32, 0, 0, 0, 0);
    if(ball == NULL)
    {
    	fprintf(stderr, "%s\n", SDL_GetError());

    	SDL_FreeSurface(screen);
    	SDL_Quit();
    	return EXIT_FAILURE;
    }
    ball_position.x = 640/2;
    ball_position.y = 480/2;
    SDL_FillRect(ball, NULL, SDL_MapRGB(ball->format, 255, 255, 255));
    SDL_BlitSurface(ball, NULL, screen, &ball_position);


    SDL_EnableKeyRepeat(10, 10);
    while(!closed)
    {
    	SDL_WaitEvent(&event);
    	switch(event.type)
    	{
    		case SDL_QUIT:
    			closed = true;
    			break;
    		case SDL_KEYDOWN:
    			if(direction)
		 		{ 
					ball_position.x +=  cos_deta * velocity_x;
		 			ball_position.y +=  sin_deta * velocity_y;
		  		}
    			break;
    		case SDL_MOUSEBUTTONDOWN:
    			if(event.button.button == SDL_BUTTON_LEFT)
    			{
    				clic.x = event.button.x;
    				clic.y = event.button.y;

    					/* Calcul de la distance entre la ball et le clic */
    				clic.x -= ball_position.x; 
    				clic.y -= ball_position.y;
    				module_z = sqrt((clic.x * clic.x) + (clic.y * clic.y));

    					/* Calcul de l'absice et de l'ordonnées 
    						SOH CAH TOA */
    				cos_deta = clic.x / module_z;
    				sin_deta = clic.y / module_z;

    					/* Coefficient directeur */
    				coefficient_directeur = (ball_position.y - clic.y) / (ball_position.x - clic.x);

    				direction = true;

    				printf("[CLIC] (%d;%d)\n", clic.x, clic.y);
     				printf("|z| = %.6f\n", module_z);
     				printf("cos ϴ : %.6f\n", cos_deta);
     				printf("sin ϴ : %.6f\n", sin_deta);
     				printf("a : %.6f\n", coefficient_directeur);

     			}
    			break;
    	}

 	 
 

    	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    	SDL_BlitSurface(ball, NULL, screen, &ball_position);

    	SDL_Flip(screen);
    }
    SDL_FreeSurface(ball);
    SDL_FreeSurface(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}
