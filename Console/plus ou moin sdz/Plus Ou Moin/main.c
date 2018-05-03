#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*********************************************************/
void empty_buffer(void);
int input_number(void);
void init_randomization(void);
int random_number(const int min, const int max);
/*********************************************************/
void print_menu(void);
void print_rules(void);
void print_level(void);
/*********************************************************/
void run(const int mystery_number);
/*********************************************************/
int main(void )
{
	char quit = 0;
	int user_input = 0;
	int random = 0;
	
	while(!quit)
	{
		print_menu();
		do 
		{
			user_input = input_number();
			empty_buffer();
		}while(user_input < 0 || user_input > 3);
		
		if(user_input != 3)
		{
			if(user_input == 2)
			{
				print_rules();
			}
			else 
			{
				print_level();
				
				do 
				{
					user_input = input_number();
					empty_buffer();
				}while(user_input < 0 || user_input > 3);
				
				switch(user_input)
				{
					case 1:
						random = random_number(0, 100);
						break;
					case 2:
						random = random_number(0, 1000);
						break;
					case 3:
						random = random_number(0, 10000);
						break;
					default:
						printf("@debug unknow choice ... EXIT_FAILURE ...\n\n");
						return EXIT_FAILURE;
				}
				
				run(random);
			}
		}
		else 
		{
			quit = 1;
		}
	}
	
	printf("@Me Goodbey thank you to play the game ...\n");
	
	return EXIT_SUCCESS;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void empty_buffer(void)
{
	char buffer = 0;
	do 
	{
		buffer = getchar(); // vide le caractere \n lors d'une saisi clavier 
	}while(buffer != '\n' && buffer != EOF); 
}
int input_number(void)
{
	int number = 0;
	while(!scanf("%d", &number));
	
	return number;
}
void init_randomization(void)
{
	srand(time(NULL)); // Initialise la graine du generateur au premier janvier 1970 
}
int random_number(const int min, const int max)
{
	init_randomization();
	return rand() % (max - min) + min; // génére une nombre aléatoire entre min et max 
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void print_menu(void)
{
	printf("=========================\n");
	printf("=(1)       Play         =\n");
	printf("=(2)       Rules        =\n");
	printf("=(3)       Quit         =\n");
	printf("=========================\n");

	printf("[+] What do you choice : ");
}
void print_rules(void)
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("Hi ! my name is robot ... I will help you ...\n\n");
	printf("I'm robot, first step you need to choose a difficulty ...\n");
	printf("next time i will count your trying point and i will indacte you\n");
	printf("if you input is superior or inferior\n\n\n");
}
void print_level(void)
{
	printf("=========================\n");
	printf("=(1)     [0, 100]       =\n");
	printf("=(2)     [0, 1000]      =\n");
	printf("=(3)     [0, 10000]     =\n");
	printf("=========================\n");
	
	printf("[+] What do you choice : ");
}
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void run(const int mystery_number)
{
	int count = 0;
	int user_input = 0;
	for(count = 0; user_input != mystery_number; count ++)
	{
		printf("[+] Proposition >> ");
		user_input = input_number();
		empty_buffer();
		printf("%d => %d", 1, mystery_number);
		if(user_input < mystery_number)
		{
			printf("@robot It's more .\n\n");
		}
		else if (user_input > mystery_number)
		{
			printf("@robot It's less .\n\n");
		}
		else 
		{
			printf("@robot you win the mystery number are %d with %d trying !\n\n\n", mystery_number, count+1);
		}
		
	}
	
}
