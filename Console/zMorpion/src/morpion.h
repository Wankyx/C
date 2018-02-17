#ifndef __MORPION__H__
#define __MORPION__H__

#define BOARD_Y 3
#define BOARD_X 3

typedef struct Graph2D
{
	unsigned int x;
	unsigned int y;
}Graph2D;

typedef struct TicTacToe
{
	/*
		board : 
			789 
			456
			123 
	*/
	char board[BOARD_Y][BOARD_X]; /* Le tableau ou se jouera le jeux */
	_Bool turn;  /* Un boolean qui va être vrai pour le tour des ron et faux pour les croix */
	int position; /* La position que le joueur va être dans le tableau */
	_Bool game_over; 
}TicTacToe;

TicTacToe TicTacToe_New(void);
void TicTacToe_Print(TicTacToe tictactoe_game);
void TicTacToe_RulesPrint(void);
_Bool TicTacToe_Set(TicTacToe* tictactoe_game, int const position);
void TicTacToe_Checker(TicTacToe* tictactoe_game);
int TicTacToe_IA(TicTacToe tictactoe_game);

#endif