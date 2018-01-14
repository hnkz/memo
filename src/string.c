#include <memolib/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_get_value(string str) {
    char* result;

    result = (char*)malloc(sizeof(char) * str.length + 1);

    if(result != NULL){
        memcpy(result, str.value, str.length);
        result[str.length] = '\0';
    }
    return result;
}

string new_string() {
    string new_str;

    new_str.length = 0;
    new_str.value  = NULL;

    return new_str;
}

int set_value(string* str, char* value) {
    size_t length   = strlen(value);
    str->length     = length;

    str->value = (char*)malloc(sizeof(char) * length);

    if(str->value != NULL) {
        memcpy(str->value, value, length);

        return 1;
    } else {
        return 0;
    }
}

string make_string(char *value) {
    string new_str = new_string();

    set_value(&new_str, value);

    return new_str;
}

void free_string(string str) {
    if(str.value != NULL) {
        free(str.value);
    }
}
