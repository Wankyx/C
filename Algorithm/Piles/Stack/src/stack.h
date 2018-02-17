#ifndef __STACK__H__
#define __STACK__H__


typedef enum Boolean Boolean;
enum Boolean 
{
	false,
	true
};

typedef struct StackInt StackInt;
struct StackInt
{
	int data;
	struct StackInt* element_next;
};

StackInt* StackInt_Create(void);
void StackInt_Destroy(StackInt* stackint);

StackInt* StackInt_Push(StackInt* stackint, int const data_stack);
StackInt* StackInt_Pop(StackInt* stackint);
int StackInt_Top(const StackInt* stackint);

Boolean StackInt_Empty(const StackInt* stackint);
void StackInt_Print(StackInt* stackint);
void StackInt_Set(StackInt* stackint, const int new_data);
unsigned int StackInt_Length(StackInt* stackint);
int StackInt_IndexOf(StackInt* stackint, unsigned int index);
void StackInt_Replace(StackInt* stackint, unsigned int index, int nvalue);
 
/*********************************************************************************************/


#endif