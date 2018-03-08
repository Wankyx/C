#include <stdio.h>
#include <stdlib.h>

#include "stringmanip.h"

int main(void)
{
	string str = String_New(10);

	String_Replace(str, "Hello, World !");
 
	String_UpperCase(str);

	printf("%s\n", str);

	String_LowerCase(str);
	printf("%s\n", str);

	String_Destroy(str);

	return EXIT_SUCCESS;
}
