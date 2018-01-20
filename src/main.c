#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memolib/memos.h>

int main(){
    printf("\033[2");
    printf("This is memo");
    return 0;
}

    // // str test
    // // String str = make_str("testてすとととa");
    // // char* cstr = get_str_value(str);
    // // printf("%s, %d\n", cstr, count_str(str));

    // // memo test
    // Memo memo1;
    // String title = make_str("A");
    // String text  = make_str("Aこれはテストテキストである！！");
    // memo1 = make_memo(title, text);

    // Memo memo2;
    // title = make_str("B");
    // text  = make_str("BこれはテストテキストBである！！");
    // memo2 = make_memo(title, text);

    // Memo memo3;
    // title = make_str("C");
    // text  = make_str("CこれはテストテキストCである！！");
    // memo3 = make_memo(title, text);

    // Memo memo4;
    // title = make_str("D");
    // text  = make_str("DこれはテストテキストDである！！");
    // memo4 = make_memo(title, text);

    // Memo memo5;
    // title = make_str("E");
    // text  = make_str("EこれはテストテキストEである！！");
    // memo5 = make_memo(title, text);

    // // show_memo(memo1);
    // // show_memo(memo2);
    // // show_memo(memo3);
    // // show_memo(memo4);
    // // show_memo(memo5);

    // Memos memos;
    // memos = new_memos();
    // add_memo(&memos, memo1);
    // add_memo(&memos, memo2);
    // add_memo(&memos, memo5);
    // add_memo(&memos, memo3);
    // add_memo(&memos, memo4);
    // remove_memo_by_title(&memos, memo5);
    // show_memos(memos);

    // free_memo(&memo1);
    // free_memo(&memo2);
    // free_memo(&memo3);
    // free_memo(&memo4);
    // free_memo(&memo5);