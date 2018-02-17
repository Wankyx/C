#include <stdio.h>
#include <stdlib.h>

#include "stringmanip.h"

string String_New(unsigned int len)
{
	string str = NULL;

	str = malloc(sizeof(len) * len);

	if(str == NULL)
		return NULL;
	*str = '\0';
	return str;
}
void String_Destroy(string str)
{
		free(str);
}

unsigned int String_Length(string str)
{
	unsigned int length = 0;
	for(length = 0; *str != '\0'; str++, length++);
	return length;
}

void String_Replace(string destination, string source)
{
	unsigned int source_len = String_Length(source);


	for(unsigned int i = 0; i < source_len; i++)
	{
		*(destination+i) = *(source+i);
	}
}

int String_Compare(string first_str, string second_str)
{
	unsigned int first_length = String_Length(first_str);
	unsigned int second_length = String_Length(second_str);
	int exit_code = 0;

	if(first_length != second_length)
		return -1;

	for(unsigned int i = 0; i < first_length; i++)
	{
		if(*(first_str+i) == *(second_str+i))
		{
			exit_code = 0;
		}
		else
		{
			return -1;
		}
	}
	return exit_code;
}
void String_Concat(string str, string to_concat)
{
	unsigned int str_length = String_Length(str);
	unsigned int to_concat_length = String_Length(to_concat);

	for(unsigned int i = str_length, j = 0; i < (to_concat_length+str_length); i++, j++)
	{
		*(str+i) = *(to_concat+j);
	}

}
