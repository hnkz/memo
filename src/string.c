#include <memolib/string.h>

char* get_str_value(String str) {
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

int set_str_value(String* str, char* value) {
    size_t length;

    length      = strlen(value);
    str->length = length;

    str->value = (char*)malloc(sizeof(char) * length + 1);

    if(str->value != NULL) {
        memcpy(str->value, value, length);
        str->value[str->length] = '\0';

        return 1;
    } else {
        return 0;
    }
}

String make_str(char *value) {
    String new_str = new_string();

    set_str_value(&new_str, value);

    return new_str;
}

String link_str(String str1, String str2) {
    char*  head;
    String str;

    head = (char*)malloc(sizeof(char) * (str1.length + str2.length + 2));
    strcat(head, str1.value);
    strcat(head, str2.value);

    set_str_value(&str, head);

    return str;
}

void free_str(String str) {
    if(str.value != NULL) {
        free(str.value);
    }
}

int count_str(String str) {
    int i;
    int count;

    count = 0;

    for(i = 0; i < str.length; i++) {
        if(str.value[i] & 0x80) {
            i += 2;
            count += 2;
        } else{
            count += 1;
        }
    }
    return count;
}


