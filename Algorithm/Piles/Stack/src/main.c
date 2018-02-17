#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(void)
{
	StackInt* stackint = StackInt_Create();
	int data = 0;


	stackint = StackInt_Push(stackint, 5626);
	stackint = StackInt_Push(stackint, 45);
	stackint = StackInt_Push(stackint, 46);
 
 	StackInt_Print(stackint);

	StackInt_Destroy(stackint);

  	return EXIT_SUCCESS;
}