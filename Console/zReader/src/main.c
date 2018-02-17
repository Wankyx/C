#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 256

int main(void)
{
	char path[STRING_LEN];
	char* content = NULL;
	char _character = 0;
	char* rt_path = NULL;

	int i = 0;

	int line = 0;
	int word = 0;
	int character = 0;

	FILE* file = NULL;


	printf("Saisir le chemin absolue : ");
	fgets(path, STRING_LEN-1, stdin);

	rt_path = strchr(path, '\n');
	*rt_path = '\0';

	printf("Chemin du fichier : %s\n", path);

	file = fopen(path, "r");

	if(file == NULL)
	{
		fprintf(stderr, "Impossible d'ouvrir le fichier en lecture !\n");
		perror("Error");
		return EXIT_FAILURE;
	}

	while(!feof(file))
	{
		character ++;
	 	_character = fgetc(file);
	}

	content = malloc(sizeof(char) * character);

	if(content == NULL)
	{
		fprintf(stderr, "Impossible d'allouer l'espace mémoire pour le contenu du fichier !\n");
		perror("Error");
		fclose(file);
		return EXIT_FAILURE;
	}
	fseek(file, 0, SEEK_SET);

	while(!feof(file))
	{	
 		content[i] = fgetc(file);
 		i++;	 
	}
	fseek(file, 0, SEEK_SET);

	for(i = 0; content[i] != '\0'; i++)
	{
		if(content[i] == ' ' || content[i] == '\n')
		{
			word++;
		}

		if(content[i] == '\n')
			line++;
	}

	printf("Contenu :\n");
	printf("%s\n\n", content);


 	printf("Nombre de caractere : %d\n", character);
 	printf("Nombre de mots : %d\n", word);
 	printf("Nombre de ligne : %d\n", (line+1));

 	free(content);
	fclose(file);

	getchar();
 

	return EXIT_SUCCESS;
}