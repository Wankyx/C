#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* 

	* - Primitive de la structure de données la files 
	* - Ajout d'un élement, retiré un element
		---------------------------------------------------------------------------------
 */

/* Fonction pour la files d'entiers */
QueueInt* QueueInt_Create(void)
{
    return NULL;
}
void QueueInt_Destroy(QueueInt* queueint)
{

}

QueueInt* QueueInt_Push(QueueInt* queueint, int const data_queue)
{
    QueueInt* first_element = QueueInt_Create();
    QueueInt* shift = QueueInt_Create();

    first_element = malloc(sizeof(*first_element));

    if(first_element == NULL)
    {
        fprintf(stderr, "C STANDARD LIBRARY ERROR : malloc()\n");
		perror("Detected Error :");
        return queueint;
    }  
    
    first_element->data = data_queue;

    if(queueint == NULL)
    {
        first_element->element_next = queueint; 
    }
    else 
    {
        shift = queueint;
        while(shift->element_next != NULL)
        {
            shift = shift->next;
        }

        first_element->element_next = shift;
    }
    return first_element;
}
QueueInt* QueueInt_Pop(QueueInt* queueint)
{
    QueueInt* last_element = QueueInt_Create();

    if(last_element == NULL)
    {
        return queueint;
    }
    
    while(queueint->element_next != NULL)
    {
        queueint = queueint->element_next;
    }
    
    last_element = queueint;
    return last_element;
}

/* FIN PRIMITIVE */
