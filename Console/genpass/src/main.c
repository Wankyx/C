#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int i = 0;
    int length = 0;
    char password_text[255];
    int password = 0;
    int multiply = 0;

    int mask = 0b0000010100111001;
    
    if(argc != 3)
    {
        fprintf(stderr, "Usage %s <name> <level>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
        
    multiply = atoi(argv[2]);
            
    if(multiply < 0)
    {
        fprintf(stderr, "Level is inferior to 1.");
        return EXIT_FAILURE;
    }   

    length = strlen(argv[1]);

    for(i = 0; i <= length; i++)
    {
        password += argv[1][i] * multiply;
    }

    password ^= mask;    
    
    printf("password number : %d\n", password);
        
    
    return EXIT_SUCCESS;
}
