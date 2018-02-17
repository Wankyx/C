#include <stdio.h>
#include <stdlib.h>
#include "stack.h"



/* 

	* - Primitive de la structure de données la piles 
	* - Ajout d'un élement, retiré un element, recuperer la valeur du sommet de la piles
		---------------------------------------------------------------------------------
 */

/* Fonction pour la piles d'entiers */
StackInt* StackInt_Create(void)
{
	return NULL;
}
void StackInt_Destroy(StackInt* stackint)
{

	while(!StackInt_Empty(stackint))
	{
		stackint = StackInt_Pop(stackint);
	}

	stackint = StackInt_Create();
}

 
StackInt* StackInt_Push(StackInt* stackint, int const data_stack)
{
	StackInt* top_element = StackInt_Create();

	top_element = malloc(sizeof(*top_element));
	
	if(top_element == NULL)
	{
		fprintf(stderr, "C STANDARD LIBRARY ERROR : malloc()\n");
		perror("Detected Error :");
		return stackint;
	}
	
	top_element->data = data_stack;
	top_element->element_next = stackint;

	return top_element;
}
StackInt* StackInt_Pop(StackInt* stackint)
{
	if(!StackInt_Empty(stackint))
	{
		StackInt* save_pointer_next_element = stackint->element_next;
		free(stackint);
		return save_pointer_next_element;
	}

	return stackint; 
}

int StackInt_Top(const StackInt* stackint)
{
	return stackint->data;
}

/* FIN PRIMITIVE */

Boolean StackInt_Empty(const StackInt* stackint)
{
	if(stackint == NULL)
		return true; 
	return false;
}
void StackInt_Print(StackInt* stackint)
{
	StackInt* p_element = stackint;
	while(!StackInt_Empty(p_element))
	{
		printf("%d\n", p_element->data);
		p_element = p_element->element_next;
	}
}
void StackInt_Set(StackInt* stackint, const int new_data)
{
	StackInt* p_begin = stackint;

	while(!StackInt_Empty(stackint))
	{
		stackint->data = new_data;
		stackint = stackint->element_next;
	}
	stackint = p_begin;
}
unsigned int StackInt_Length(StackInt* stackint)
{
	unsigned int stackint_length = 0;
	StackInt* p_begin = stackint;
	while(!StackInt_Empty(stackint))
	{
		stackint = stackint->element_next;
		stackint_length ++;
	}
	stackint = p_begin;

	return stackint_length;
}
int StackInt_IndexOf(StackInt* stackint, unsigned int index)
{
	unsigned int i = 0;
	int recv_data = 0;

	if(index < 0 || index > StackInt_Length(stackint) || StackInt_Empty(stackint))
		return -1;
 

	StackInt* p_begin = stackint;
	for(i = 0; i != index; i++)
	{
		stackint = stackint->element_next;
	}
	recv_data = stackint->data;

	stackint = p_begin;
	return recv_data;
}
void StackInt_Replace(StackInt* stackint, unsigned int index, int nvalue)
{
	unsigned int i = 0;

	if(index < 0 || index > StackInt_Length(stackint) || StackInt_Empty(stackint))
		return;

	StackInt* p_begin = stackint;
	for(i = 0; i != index; i++)
	{
		stackint = stackint->element_next;
	}
	stackint->data = nvalue;
	stackint = p_begin;
}
/*********************************************************************************************/

