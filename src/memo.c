#include <memolib/memo.h>

Memo new_memo() {
    Memo memo;

    memo.title  = new_string();
    memo.text   = new_string();
    memo.str    = new_string();

    return memo;
}

Memo make_memo(String title, String text) {
    Memo memo;

    memo = new_memo();

    memo.title  = title;
    memo.text   = text;
    memo.str    = link_str(title, text);

    return memo;
}

int set_title(Memo* memo, char* title) {
    return set_str_value(&(memo->title), title);
}

int set_text(Memo* memo, char* text) {
    return set_str_value(&(memo->text), text);
}

int set_str(Memo* memo, char* str) {
    return set_str_value(&(memo->str), str);
}

void free_memo(Memo memo) {
    free_str(memo.title);
    free_str(memo.text);
    free_str(memo.str);
}

void show_memo(Memo memo) {
    int i;
    size_t title_len = memo.title.length;
    size_t text_len  = memo.text.length;

    for(i = 0; i < title_len; i++)
        printf("--");
    printf(" title ");
    for(i = 0; i < title_len; i++)
        printf("--");
    printf("\n");

    printf("%s\n", memo.title.value);

    for(i = 0; i < title_len; i++)
        printf("--");
    printf(" text ");
    for(i = 0; i < title_len; i++)
        printf("--");
    printf("-\n");

    printf("%s\n", memo.text.value);

    for(i = 0; i < title_len * 2; i++)
        printf("--");
    printf("-------\n");
}
