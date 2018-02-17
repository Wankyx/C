/*
        EAT EAT IN THE MATRIX VERSIONS 1.1
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#include <windows.h>
#include <mmsystem.h>

#define MATRIX_ALLOC_Y 20
#define MATRIX_ALLOC_X 42

#define STRING_ALLOC 256

#define MAP_DEFAULT_ASCII 219
#define NEW_LINE putchar('\n')

typedef struct Graphics Graphics;
typedef struct Matrix Matrix;
typedef struct Entity Entity;

struct Graphics
{
    int x;
    int y;
};

struct Matrix
{
    char map[MATRIX_ALLOC_Y][MATRIX_ALLOC_X];
};

struct Entity
{
    char letter;
    Graphics entity;
};

struct Matrix Matrix_init(void);
void print_matrix(struct Matrix matrix);
void player_move(Entity* move, short vkey);
char* main_menu(void);
void stop(void);
void console_change_color(int background, int foreground);

int main(void)
{
    int song = 0;
    size_t player_score = 0;
    char username[STRING_ALLOC];
    Matrix matrix = Matrix_init();
    Entity player = {'-'};
    Entity enemi  = {'+'};
    Graphics set = {0, 0};
    srand(time(NULL));

    song = rand() % 2;


    strcpy(username, main_menu());
    username[strlen(username) - 1] = '\0'; // retire de \n
    if(song == 1)
    {
        PlaySound((LPCSTR)"son2.wav", GetModuleHandle(NULL), SND_ASYNC);
        stop();
    }
    else
    {
        PlaySound((LPCSTR)"son3.wav", GetModuleHandle(NULL), SND_ASYNC);
    }


    enemi.entity.y = MATRIX_ALLOC_Y/2;
    enemi.entity.x = MATRIX_ALLOC_X/2;

    player.entity.y = MATRIX_ALLOC_Y % 6;
    player.entity.x = MATRIX_ALLOC_X % 6;

    matrix.map[enemi.entity.y ][enemi.entity.x] = enemi.letter;
    matrix.map[player.entity.y][player.entity.x] = player.letter;
    print_matrix(matrix);

    NEW_LINE;
    printf("Waiting song :\n");
    while(1)
    {
        while(!kbhit())
        {
            {
                static int i = 0;
                console_change_color(i, i);
                i++;
            }
        }
        switch(getch())
        {
        case 122:
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
            player.entity.y--;
            break;
        case 115:
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
            player.entity.y++;
            break;
        case 113:
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
            player.entity.x--;
            break;
        case 100:
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
            player.entity.x++;
            break;
        case 27:
            return EXIT_SUCCESS;
        }
        system("cls");
        console_change_color(0, 15);
        printf("[+] %s -> Score : ", username);
        console_change_color(0, 4);
        printf("%d\n", player_score);

        matrix.map[player.entity.y][player.entity.x] = player.letter;
        print_matrix(matrix);

        if((player.entity.x == enemi.entity.x) && (player.entity.y == enemi.entity.y))
        {
            player_score++;
            enemi.entity.y = rand() % MATRIX_ALLOC_Y;
            enemi.entity.x = rand() % MATRIX_ALLOC_X;

            if(enemi.entity.y <= 0)
            {
                while(enemi.entity.y <= 0)
                {
                    enemi.entity.y = rand() % MATRIX_ALLOC_Y;
                }
            }
            else if(enemi.entity.y >= MATRIX_ALLOC_Y)
            {
                while(enemi.entity.y <= 0)
                {
                    enemi.entity.y = rand() % MATRIX_ALLOC_Y;
                }
            }

            if(enemi.entity.x <= 0)
            {
                while(enemi.entity.x)
                {
                    enemi.entity.x = rand() % MATRIX_ALLOC_X;
                }
            }
            else if(enemi.entity.x >= MATRIX_ALLOC_X)
            {
                while(enemi.entity.x)
                {
                    enemi.entity.x = rand() % MATRIX_ALLOC_X;
                }
            }

            matrix.map[enemi.entity.y][enemi.entity.x] = enemi.letter;
        }
        if(player.entity.x == MATRIX_ALLOC_X - 1)
        {
             matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
             player.entity.x--;
             matrix.map[player.entity.y][player.entity.x] = player.letter;
        }
        else if(player.entity.x == 0)
        {
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
             player.entity.x++;
             matrix.map[player.entity.y][player.entity.x] = player.letter;
        }

        if(player.entity.y == MATRIX_ALLOC_Y - 1)
        {
            matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
            player.entity.y--;
            matrix.map[player.entity.y][player.entity.x] = player.letter;
        }
        else if(player.entity.y == 0)
        {
             matrix.map[player.entity.y][player.entity.x] = MAP_DEFAULT_ASCII;
             player.entity.y++;
             matrix.map[player.entity.y][player.entity.x] = player.letter;
        }
        //Sleep(120); retirer pour cause de "fluiditer"
    }

    return 0;
}

struct Matrix Matrix_init(void)
{
    Matrix matrix;
    Graphics set;
    for(set.y = 0; set.y  < MATRIX_ALLOC_Y; set.y ++)
    {
        for(set.x = 0; set.x < MATRIX_ALLOC_X; set.x++)
        {
            matrix.map[set.y][set.x] = MAP_DEFAULT_ASCII;
        }
    }
    return matrix;
}
void print_matrix(struct Matrix matrix)
{
    Graphics set;

    NEW_LINE;
    putchar('\t');

    for(set.y = 0; set.y < MATRIX_ALLOC_Y; ++set.y)
    {
        for(set.x = 0; set.x < MATRIX_ALLOC_X; ++set.x)
        {
            console_change_color(0, 15);
            if(matrix.map[set.y][set.x] == '-')
            {
                console_change_color(0, 12);
                printf("%c", matrix.map[set.y][set.x]);
            }
            else
            {
                printf("%c", matrix.map[set.y][set.x]);
            }
        }
        NEW_LINE;
        putchar('\t');
    }
}
char* main_menu(void)
{
    char username[STRING_ALLOC];
    char title_game[STRING_ALLOC] = "=Eat Eat In the Matrix=";
    char buffer = 0;
    size_t i = 0, lenght = 0;
    int choice = 0, convert_scanf_error = 0;
    PlaySound((LPCSTR)"menu.wav", GetModuleHandle(NULL), SND_ASYNC);
    lenght = strlen(title_game);


/*
    for(i = 0; i < 400; i++)
    {
        printf("[%d]TEXT\n", i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i | i);
    }
*/
    printf("\t\t\t\t");
    console_change_color(0, 2);
    for(i = 0; i < lenght; i++)
    {
        putchar('=');
        Sleep(255);
    }
    NEW_LINE;
    printf("\t\t\t\t");
    for(i = 0; i < lenght+1; i++)
    {
        putchar(title_game[i]);
        Sleep(255);
    }
    NEW_LINE;
    printf("\t\t\t\t");
    for(i = 0; i < lenght; i++)
    {
        putchar('=');
        Sleep(255);
    }
    NEW_LINE;
    NEW_LINE;
    NEW_LINE;
    console_change_color(0, 15);
    i = 0;
    printf("[+] What is your name : ");
    console_change_color(0, 6);
    while(buffer != '\n')
    {
        buffer = getchar();
        username[i] = buffer;
        i++;
    }
    username[i] = '\0';

    console_change_color(0, 15);
    printf("[+] Hello ");
    console_change_color(0, 6);
    printf("%s\n", username);

    console_change_color(0, 2);
    printf("\t\t\t\t\t");
    printf("===MENU===\n");
    printf("\t\t\t\t");
    printf("\t 1.Play\n");
    printf("\t\t\t\t");
    printf("\t 2.Rules\n");

    do
    {
        console_change_color(0, 15);
        printf("[+] Select your choose : ");
        console_change_color(0, 6);
        convert_scanf_error = scanf("%d", &choice);
        if(convert_scanf_error == 0)
        {
            console_change_color(0, 12);
            puts("[!] You Enter a letter");
            do
            {
                buffer = getchar();
            }while(buffer != '\n' && buffer != EOF);
        }
    }while(choice != 1 && choice != 2);

    if(choice == 2)
    {
        NEW_LINE;
        NEW_LINE;
        console_change_color(0, 14);
        printf("[MAXIMUS-2025] Hello my name is MAXIMUS-2025\n");
        printf("I will assist you for increment you score if you touch a '+' !\n");
        printf("your enemi is + eat him !!!\n");
        username[strlen(username)-1] = '\0';

        console_change_color(0, 11);
        NEW_LINE;
        printf("[%s] Mmmmm Okay how i can move ?\n", username);

        NEW_LINE;
        console_change_color(0, 14);
        printf("[MAXIMUS-2025] Ha i forgot this information !\n");
        printf("I'm french ! you need use z to go up, s to go down, q to go left, d to go right !\n");
        printf("BEY BEY !\n");
        console_change_color(0, 15);
        do
        {
            buffer = getchar();
        }while(buffer != '\n' && buffer != EOF);
        main_menu();
    }
    stop();
    return username;
}

void stop(void)
{
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        putchar('.');
        Sleep(500);
        putchar('.');
        Sleep(500);
        putchar('.');


        putchar('\r');
        putchar('\r');
        putchar('\r');

        putchar(' ');
        putchar(' ');
        putchar(' ');


        putchar('\r');
        putchar('\r');
        putchar('\r');
        putchar('\r');
        Sleep(500);
    }
}
void console_change_color(int background, int foreground)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, background | foreground);
}
