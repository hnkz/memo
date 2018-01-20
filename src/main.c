#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <locale.h>

#include <memolib/memos.h>

void    show_menu();
void    print_start_window();
void    execute_menu();

Memos   root;
Memos*  next_memos;
int     x, y, w, h;
int     menu_status;
int     memo_status;
int     key;

char*  menus[] = {
    "メモを追加",
    "メモを削除",
    "メモを編集",
    "メモを検索"
};

int menu_size = sizeof(menus)/sizeof(char *);

void show_menu() {
    int i;

    clear();
    y = 0;
    x = 0;

    show_memos_with_select(*next_memos, memo_status);

    y = h-1;
    x = 0;
    move(y, x);


    for(i = 0; i < menu_size; i++) {
        if(i == menu_status) {
            attrset(COLOR_PAIR(1));
            printw(menus[i]);
            attrset(COLOR_PAIR(2));
        } else {
            printw(menus[i]);
        }
        printw(" ");
    }

    refresh();
}

void print_start_window() {
    while (1) {
        show_menu();

        key = getch();
        if (key == 'q') break;
        switch(key) {
            case KEY_UP:
                if(next_memos->before != NULL)
                    next_memos = next_memos->before;
                if(memo_status > 0)
                    memo_status -= 1;
                break;
            case KEY_DOWN:
                if(next_memos->next != NULL)
                    next_memos = next_memos->next;
                if(memo_status < 3)
                    memo_status += 1;
                break;
            case KEY_LEFT:
                if(menu_status == 0)
                    menu_status = menu_size-1;
                else 
                    menu_status -= 1;
                break;
            case KEY_RIGHT:
                if(menu_status == menu_size-1)
                    menu_status = 0;
                else
                    menu_status += 1;
                break;
            case '\n':
                execute_menu();
                break;
            case 'h':

                break;
            default:

                break;
        }
    }
}

void execute_menu() {
    
}

int main(){
    // 基本はrootでメモを管理
    // 初期化処理
    menu_status = 0;
    memo_status = 0;
    setlocale(LC_ALL, ""); // 日本語
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(2));
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, h, w);
    curs_set(0);
    clear();

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

    Memo memo6;
    title = make_str("F");
    text  = make_str("FこれはテストテキストFである！！");
    memo6 = make_memo(title, text);

    Memo memo7;
    title = make_str("G");
    text  = make_str("GこれはテストテキストGである！！");
    memo7 = make_memo(title, text);

    Memo memo8;
    title = make_str("H");
    text  = make_str("HこれはテストテキストHである！！");
    memo8 = make_memo(title, text);


    root        = new_memos();
    next_memos  = &root;
    add_memo(&root, memo1);
    add_memo(&root, memo2);
    add_memo(&root, memo3);
    add_memo(&root, memo4);
    add_memo(&root, memo5);
    // add_memo(&root, memo6);
    // add_memo(&root, memo7);
    // add_memo(&root, memo8);


    //remove_memo_by_title(&root, memo5);

    // 画面の初期化
    print_start_window();

    endwin();
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