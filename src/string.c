#include <memolib/string.h>

char* string_get_value(String str) {
    char* result;

    result = (char*)malloc(sizeof(char) * str.length + 1);

    if(result != NULL){
        memcpy(result, str.value, str.length);
        result[str.length] = '\0';
    }
    return result;
}

String new_string() {
    String new_str;

    new_str.length = 0;
    new_str.value  = NULL;

    return new_str;
}

int set_value(String* str, char* value) {
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

String make_string(char *value) {
    String new_str = new_string();

    set_value(&new_str, value);

    return new_str;
}

void free_string(String str) {
    if(str.value != NULL) {
        free(str.value);
    }
}
