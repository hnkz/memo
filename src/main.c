#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memolib/memos.h>

int main(){
    // str test
    // String str = make_str("testてすとととa");
    // char* cstr = get_str_value(str);
    // printf("%s, %d\n", cstr, count_str(str));

    // memo test
    Memo memo1;
    String title = make_str("A");
    String text  = make_str("Aこれはテストテキストである！！");
    memo1 = make_memo(title, text);

    Memo memo2;
    title = make_str("B");
    text  = make_str("BこれはテストテキストBである！！");
    memo2 = make_memo(title, text);

    Memo memo3;
    title = make_str("C");
    text  = make_str("CこれはテストテキストCである！！");
    memo3 = make_memo(title, text);

    Memo memo4;
    title = make_str("D");
    text  = make_str("DこれはテストテキストDである！！");
    memo4 = make_memo(title, text);

    Memo memo5;
    title = make_str("E");
    text  = make_str("EこれはテストテキストEである！！");
    memo5 = make_memo(title, text);

    show_memo(memo1);
    show_memo(memo2);
    show_memo(memo3);
    show_memo(memo4);
    show_memo(memo5);

    return 0;
}
