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
Memos*  selected_memos;
int     x, y, w, h;
int     menu_status;
int     memo_status;
int     key;

char* desctiption = "操作方法 j: 下, k: 上, h: 左, l: 右, Enter: 決定, x: ヘルプ, q: 終了";

char*  menus[] = {
    "メモを追加",
    "メモを削除",
    "メモを編集",
    "メモを並び替え",
    "メモを検索",
};

int menu_size = sizeof(menus)/sizeof(char *);

void show_menu() {
    int i;

    clear();

    // メモを表示
    show_memos_with_select(*selected_memos, memo_status);

    // メニューを表示
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

    printw("  %s", desctiption);

    refresh();
}

void print_start_window() {
    while (1) {
        // メニューを表示
        show_menu();

        key = getch();
        if (key == 'q') break;
        switch(key) {
            case KEY_UP:
            case 'k':
                if(selected_memos->before != NULL)
                    selected_memos = selected_memos->before;
                if(memo_status > 0)
                    memo_status -= 1;
                break;
            case KEY_DOWN:
            case 'j':
                if(selected_memos->next != NULL)
                    selected_memos = selected_memos->next;
                if(memo_status < 3)
                    memo_status += 1;
                break;
            case KEY_LEFT:
            case 'h':
                if(menu_status == 0)
                    menu_status = menu_size-1;
                else 
                    menu_status -= 1;
                break;
            case KEY_RIGHT:
            case 'l':
                if(menu_status == menu_size-1)
                    menu_status = 0;
                else
                    menu_status += 1;
                break;

            case 'x':
            case '\n':
                execute_menu();
                break;
            default:

                break;
        }
    }
}

void print_add_memo_window() {
    String title;
    String text;
    Memo   memo;
    char* tmp;

    tmp = malloc(sizeof(char *));

    clear();
    echo();

    printw("メモタイトルを入力してください: ");
    scanw("%s", tmp);
    title = make_str(tmp);
    
    printw("メモの内容を入力してください: ");
    scanw("%s", tmp);
    text = make_str(tmp);

    memo = make_memo(title, text);
    add_memo(selected_memos, memo);

    free(tmp);

    noecho();
}

void print_edit_memo_window() {
    Memos* remove_memos;
    clear();
    echo();

    remove_memos = selected_memos;

    show_memo(selected_memos->memo);
    printw("\nこのメモを削除しますか？(y/n)");
    while(1){
        key = getch();
        if(key == 'y'){
            if(remove_memos->before == NULL)
                root = new_memos();
            remove_memo(remove_memos);
            break;
        } else if(key == 'n'){
            break;
        }
    }

    selected_memos = &root;

    noecho();
}

void print_remove_memo_window() {

}

void print_sort_memo_window() {

}

void print_search_memo_window() {

}

void execute_menu() {
    switch(menu_status) {
        case 0:
            print_add_memo_window();
            break;
        case 1:
            if(selected_memos->memo.title.value != NULL)
                print_edit_memo_window();
            break;
        case 2:
            if(selected_memos->memo.title.value != NULL)
                print_remove_memo_window();
            break;
        case 3:
            if(selected_memos->memo.title.value != NULL)
                print_sort_memo_window();
            break;
        case 4:
            if(selected_memos->memo.title.value != NULL)
                print_search_memo_window();
            break;
    }
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
    noecho(); // 入力見えないように
    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, h, w);
    curs_set(0);
    clear();

    root            = new_memos();
    selected_memos  = &root;

    // 画面の初期化
    print_start_window();

    endwin();
    return 0;
}