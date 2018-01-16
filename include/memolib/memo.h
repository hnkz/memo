#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memolib/string.h>

typedef struct {
    String      title;
    String      text;
    String      str;
} Memo;

Memo    new_memo();
Memo    make_memo(String title, String text);
int     set_title(Memo* memo, char* title);
int     set_text(Memo* memo, char* text);
int     set_str(Memo* memo, char* str);
void    free_memo(Memo memo);
void    show_memo(Memo memo);
