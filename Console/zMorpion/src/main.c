#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "morpion.h"

static void empty_buffer(void)
{
	char buff = 0;
	do
	{
		buff = getchar();
	}while(buff != '\n' && buff != EOF);
}



int main(void)
{
	TicTacToe tictactoe = TicTacToe_New();
	_Bool bad_input = false;

	TicTacToe_RulesPrint();

	while(!tictactoe.game_over)
	{
 		switch((int)tictactoe.turn)
		{
			case 1:
				printf("C'est au tour des croix :\n");
				scanf("%d", &tictactoe.position);

				
				bad_input = TicTacToe_Set(&tictactoe, tictactoe.position);

			 	while(bad_input)
			 	{
					printf("/!\\ Echec: Veuillez ne pas jouer dans une case deja jouer !\n");		
					empty_buffer();
					
					scanf("%d", &tictactoe.position);
					bad_input = TicTacToe_Set(&tictactoe, tictactoe.position);
				}

				tictactoe.turn = false;
				break;
			case 0:
 				printf("C'est au tour des rond :\n");
				scanf("%d", &tictactoe.position);

				bad_input = TicTacToe_Set(&tictactoe, tictactoe.position);
			 	while(bad_input)
			 	{
					printf("/!\\ Echec: Veuillez ne pas jouer dans une case deja jouer !\n");		
					empty_buffer();

					scanf("%d", &tictactoe.position);
					bad_input = TicTacToe_Set(&tictactoe, tictactoe.position);
				}

				tictactoe.turn = true;
				break;
			default:
				fprintf(stderr, "Une erreur est survenu lors de l'execution du programme !\n");
				break;	
		}

		TicTacToe_Checker(&tictactoe);

		if(tictactoe.game_over == true)
		{
			printf("Fin du jeux !\n");
		}

		TicTacToe_Print(tictactoe);
		getchar();
	}
	getchar();
	return EXIT_SUCCESS;
}