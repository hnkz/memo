#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memolib/memos.h>

int main(){
    // str test
    String str = make_str("test");
    char* cstr = get_str_value(str);
    printf("%s\n", cstr);

    // memo test
    Memo memo;
    String title = make_str("Test title");
    String text  = make_str("This is Test text.");
    memo = make_memo(title, text);
    show_memo(memo);

    return 0;
}
