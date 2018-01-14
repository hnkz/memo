
typedef struct {
    char*   value;
    int     length;
} string;

char*   string_get_value(string str);
string  new_string();
int     set_value(string* str, char* char_str);
string  make_string(char *value);
void    free_string(string str);
