#ifndef __STRINGMANIP__H__
#define __STRINGMANIP__H__

typedef char* string;

string String_New(unsigned int len);
void String_Destroy(string str);

unsigned int String_Length(string str);
void String_Replace(string destination, string source);
int String_Compare(string first_str, string second_str);
void String_Concat(string str, string to_concat);

#endif
