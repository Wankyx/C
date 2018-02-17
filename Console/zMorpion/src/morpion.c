#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "morpion.h"

TicTacToe TicTacToe_New(void)
{
	TicTacToe tictactoe_game;
	Graph2D position = {0, 0};

	for(position.y = 0; position.y < BOARD_Y; position.y++)
	{
		for(position.x = 0; position.x < BOARD_X; position.x++)
		{
			tictactoe_game.board[position.y][position.x] = '-';
		}
	}

	/*
		true  = croix
		false = rond
	*/
	tictactoe_game.turn = true; 
	tictactoe_game.position = 0;
	tictactoe_game.game_over = false;


	return tictactoe_game;
}
void TicTacToe_Print(TicTacToe tictactoe_game)
{
	Graph2D position = {0, 0};

	for(position.y = 0; position.y < BOARD_Y; position.y++)
	{
		for(position.x = 0; position.x < BOARD_X; position.x++)
		{
			printf("%c\t", tictactoe_game.board[position.y][position.x]);
		}
		printf("\n");
	}
}

void TicTacToe_RulesPrint(void)
{
	printf("7\t8\t9\n");
	printf("4\t5\t6\n");
	printf("1\t2\t3\n");
}

_Bool TicTacToe_Set(TicTacToe* tictactoe_game, int const position)
{
	switch(position)
	{
		case 1:
			if(tictactoe_game->board[2][0] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[2][0] = 'X';
				}
				else 
				{
					tictactoe_game->board[2][0] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 2:
			if(tictactoe_game->board[2][1] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[2][1] = 'X';
				}
				else 
				{
					tictactoe_game->board[2][1] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 3:
			if(tictactoe_game->board[2][2] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[2][2] = 'X';
				}
				else 
				{
					tictactoe_game->board[2][2] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 4:
			if(tictactoe_game->board[1][0] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[1][0] = 'X';
				}
				else 
				{
					tictactoe_game->board[1][0] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 5:
			if(tictactoe_game->board[1][1] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[1][1] = 'X';
				}
				else 
				{
					tictactoe_game->board[1][1] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 6:
			if(tictactoe_game->board[1][2] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[1][2] = 'X';
				}
				else 
				{
					tictactoe_game->board[1][2] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 7:
			if(tictactoe_game->board[0][0] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[0][0] = 'X';
				}
				else 
				{
					tictactoe_game->board[0][0] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 8:
			if(tictactoe_game->board[0][1] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[0][1] = 'X';
				}
				else 
				{
					tictactoe_game->board[0][1] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
		case 9:
			if(tictactoe_game->board[0][2] == '-')
			{
				if(tictactoe_game->turn == true)
				{
					tictactoe_game->board[0][2] = 'X';
				}
				else 
				{
					tictactoe_game->board[0][2] = 'O';
				}
				return false;
			}
			else
			{
				return true;
			}
			break;
	}
	return true;
}
void TicTacToe_Checker(TicTacToe* tictactoe_game)
{
	Graph2D position = {0, 0};
	int align = 0;

	for(position.y = 0; position.y < BOARD_Y; position.y++)
	{
		for(position.x = 0; position.x < BOARD_X; position.x++)
		{
			if(tictactoe_game->board[position.y][position.x] == 'O')
			{
				align++;
				if(align == 3)
				{
					tictactoe_game->game_over = true;
					return;
				}
			}
		}
		align = 0;
	}

	align = 0;

	for(position.y = 0; position.y < BOARD_Y; position.y++)
	{
		for(position.x = 0; position.x < BOARD_X; position.x++)
		{
			if(tictactoe_game->board[position.y][position.x] == 'X')
			{
				align++;
				if(align == 3)
				{
					tictactoe_game->game_over = true;
					return;
				}
			}
		}
		align = 0;
	}

	align = 0;

	for(position.x = 0; position.x < BOARD_X; position.x++)
	{
		for(position.y = 0; position.y < BOARD_Y; position.y++)
		{
			if(tictactoe_game->board[position.y][position.x] == 'O')
			{
				align++;
				if(align == 3)
				{
					tictactoe_game->game_over = true;
					return;
				}
			}
		}
		align = 0;
	}

	align = 0;

	for(position.x = 0; position.x < BOARD_X; position.x++)
	{
		for(position.y = 0; position.y < BOARD_Y; position.y++)
		{
			if(tictactoe_game->board[position.y][position.x] == 'X')
			{
				align++;
				if(align == 3)
				{
					tictactoe_game->game_over = true;
					return;
				}
			}
		}
		align = 0;
	}

	align = 0;

	for(position.x = 0, position.y = 0; position.y < BOARD_Y; position.y++, position.x++)
	{
		if(tictactoe_game->board[position.y][position.x] == 'O')
		{
			align++;
			if(align == 3)
			{
				tictactoe_game->game_over = true;
				return;
			}
		}
	}

	align = 0;

	for(position.x = 0, position.y = 0; position.y < BOARD_Y; position.y++, position.x++)
	{
		if(tictactoe_game->board[position.y][position.x] == 'X')
		{
			align++;
			if(align == 3)
			{
				tictactoe_game->game_over = true;
				return;
			}
		}
	}

	align = 0;

	for(position.x = 2, position.y = 0; position.y < BOARD_Y; position.y++, position.x--)
	{
		if(tictactoe_game->board[position.y][position.x] == 'O')
		{
			align++;
			if(align == 3)
			{
				tictactoe_game->game_over = true;
				return;
			}
		}
	}

	align = 0;

	for(position.x = 2, position.y = 0; position.y < BOARD_Y; position.y++, position.x--)
	{
		if(tictactoe_game->board[position.y][position.x] == 'X')
		{
			align++;
			if(align == 3)
			{
				tictactoe_game->game_over = true;
				return;
			}
		}
	}

}
int TicTacToe_IA(TicTacToe tictactoe_game)
{
	char cpy_board[9];
	Graph2D position = {0, 0};
	_Bool is_sort = false;
	char tmp_val = 0;

		// Copier les élément
	cpy_board[0] = tictactoe_game.board[0][0];
	cpy_board[1] = tictactoe_game.board[0][1];
	cpy_board[2] = tictactoe_game.board[0][2];
	cpy_board[3] = tictactoe_game.board[1][0];
	cpy_board[4] = tictactoe_game.board[1][1];
	cpy_board[5] = tictactoe_game.board[1][2];
	cpy_board[6] = tictactoe_game.board[2][0];
	cpy_board[7] = tictactoe_game.board[2][1];
	cpy_board[8] = tictactoe_game.board[2][2];
 

	while(!is_sort)
	{
		is_sort = true;
		for(position.x = 0; position.x < BOARD_X; position.x++)
		{
			if(cpy_board[position.x] > cpy_board[position.x + 1])
			{
				is_sort = false;
				tmp_val = cpy_board[position.x];
				cpy_board[position.x] = cpy_board[position.x+1];
				cpy_board[position.x+1] = tmp_val;
			}
		}
	}
	 

}