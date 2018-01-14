#include <memolib/memo.h>

Memo new_memo() {
    Memo memo;

    memo.title  = new_string();
    memo.text   = new_string();
    memo.str    = new_string();

    return memo;
}

Memo make_memo(char* title, char* text) {
    Memo memo;

    memo = new_memo();

    set_title(&memo, title);
    set_text(&memo, text);
    set_str(&memo, strcat(title, text));

    return memo;
}

int set_title(Memo* memo, char* title) {
    return set_value(&(memo->title), title);
}

int set_text(Memo* memo, char* text) {
    return set_value(&(memo->text), text);
}

int set_str(Memo* memo, char* str) {
    return set_value(&(memo->str), str);
}
