#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char*   value;
    int     length;
} String;

String  new_string();
char*   get_str_value(String str);
int     set_str_value(String* str, char* char_str);
String  make_str(char *value);
String  link_str(String str1, String str2);
void    free_str(String str);
