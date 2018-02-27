#include <stdio.h>
#include <stdlib.h>

void selection_sort_c(int* array, const int length)
{
	int tmp = 0;
	int min = 0;
	int i = 0, j = 0;


	for(i = 0; i < length - 1; i++)
	{
		min = i;
		for(j = i+1; j < length ;j++)
		{
			if(array[j] < array[min])
			{
				min = j; 
			}
		}

		if(min != i)
		{
			tmp = array[min];
			array[min] = array[i];
			array[i] = tmp;
		}

	}

}

int main(void)
{
    size_t i = 0;
	int array[10] = {45, 21, 32, 51, 121, -66, 0, 9, 10, 11};


	printf("Tableau non trier :\n");

	for(i = 0; i < 10; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n\n--------------------------\n");

	selection_sort_c(array, 10);	

	printf("\nTableau trier :\n");

	for(i = 0; i < 10; i++)
	{
		printf("%d ", array[i]);
	}
    return EXIT_SUCCESS;
}
