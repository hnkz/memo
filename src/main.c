#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <memolib/memos.h>

#define clr             printf("\033[2J") // 画面をクリア
#define clr_right       printf("\033[0K") //カーソル位置からその行の右端までをクリア
#define clr_left        printf("\033[1K") //カーソル位置からその行の左端までをクリア
#define clr_line        printf("\033[2K") //カーソル位置の行をクリア
#define location(x, y)   printf("\033[%d;%dH" ,y,x) //カーソル位置を移動
#define right(x)        printf("\033[%dC" ,x) //カーソルを指定数だけ右に移動
#define left(x)         printf("\033[%dD" ,x) //カーソルを指定数だけ左に移動
#define down(x)         printf("\033[%dB" ,x) //カーソルを指定数だけ下に移動
#define up(x)           printf("\033[%dA" ,x) //カーソルを指定数だけ上に移動

int get_window_width() {
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        return ws.ws_col;
    }

    return -1;
}

int get_window_height() {
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        return ws.ws_row;
    }

    return -1;
}

void print_start_window() {
    int win_row;
    win_row = get_window_height();

    clr
    location(0, win_row);
    printf("メモを追加 メモを削除 メモを編集\n");
}

int main(){
    // 基本はrootでメモを管理
    Memos root;

    // 画面の初期化
    print_start_window();

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