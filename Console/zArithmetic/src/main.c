#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int input_number = 0;
	int a = 0;
	int b = 0;

	int i = 0;

	int correct = 0;
	int bad = 0;

	clock_t t;

	srand(time(NULL));

	printf("** zArithmetic (niveau 3) **\n");
	printf("Ce programme va vous soumettre dix calculs simples, calculs que vous allez devoir resoudre de tete le plus rapidement possible !\n");

	while(i < 10)
	{

		switch(rand() % 4)
		{
			case 0:
			 	a = rand() % 10;
				b = rand() % 10;
				printf("\t%d + %d = ", a, b);
				scanf("%d", &input_number);

				if((a + b) == input_number)
				{
					printf("\n\t\tCorrecte !\n");
					correct++;
				}
				else 
				{
					printf("\n\t\tFaux !\n");
				}
				break;
			case 1:
				a = rand() % 10;
				b = rand() % 10;
				printf("\t%d - %d = ", a, b);
				scanf("%d", &input_number);

				if((a - b) == input_number)
				{
					printf("\n\t\tCorrecte !\n");
					correct++;
				}
				else 
				{
					printf("\n\t\tFaux !\n");
				}
				break;
			case 2:
				a = rand() % 10;
				b = rand() % 10;
				printf("\t%d * %d = ", a, b);
				scanf("%d", &input_number);

				if((a * b) == input_number)
				{
					printf("\n\t\tCorrecte !\n");
					correct++;
				}
				else 
				{
					printf("\n\t\tFaux !\n");
				}
				break;
			case 3:
				a = rand() % 10;
				b = rand() % 10;

				if(b == 0)
				{
					while(b == 0)
						b = rand()%10;
					
				}

				printf("\t%d / %d = ", a, b);
				scanf("%d", &input_number);

				if((a / b) == input_number)
				{
					printf("\n\t\tCorrecte !\n");
					correct++;
				}
				else 
				{
					printf("\n\t\tFaux !\n");
				}
				break;
		}
		i++;
	}
	t = clock();
	bad = 10 - correct;

	printf("Reponses correctes : %d/10 | Pourcentage : %.0f%%\n", correct, ((float)correct/10.0) * 100.0);
	printf("Reponse fausses : %d/10    | Pourcentage : %.0f%%\n", bad,  ((float)bad/10.0) * 100.0);
	printf("Duree totale : %.0f secondes\n", (double)t/CLOCKS_PER_SEC);
	printf("Duree moyenne par operation : %.2f secondes\n", (double)(t / CLOCKS_PER_SEC)/10.0);

	getchar();
	getchar();
	return EXIT_SUCCESS;
}