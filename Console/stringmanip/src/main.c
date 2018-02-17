#include <stdio.h>
#include <stdlib.h>

#include "stringmanip.h"

int main(void)
{
	string str = String_New(10);
	string str2 = String_New(4);

	String_Replace(str, "he");
	String_Concat(str, "llo");
	printf("%s\n", str);

	String_Destroy(str);

	return EXIT_SUCCESS;
}
