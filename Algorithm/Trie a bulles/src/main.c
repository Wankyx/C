#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 

void buble_sort_c(int* array, const int length)
{
	_Bool is_sort = false;
	int tempory = 0;
	size_t i = 0;

	while(!is_sort)
	{
		is_sort = true;
		for(i = 0; i < length; i++)
		{
			if(array[i] > array[i+1])
			{
				tempory = array[i];
				array[i] = array[i+1];
				array[i+1] = tempory;
				is_sort = false;
			}
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

	buble_sort_c(array, 10);	

	printf("\nTableau trier :\n");

	for(i = 0; i < 10; i++)
	{
		printf("%d ", array[i]);
	}

	return EXIT_SUCCESS;
}
