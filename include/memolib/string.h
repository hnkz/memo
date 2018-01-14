#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char*   value;
    int     length;
} String;

char*   string_get_value(String str);
String  new_string();
int     set_value(String* str, char* char_str);
String  make_string(char *value);
void    free_string(String str);
