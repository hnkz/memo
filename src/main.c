#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <locale.h>

#include <memolib/memos.h>

#define BUFSIZE 64

void    show_menu();
void    print_start_window();
void    execute_menu();

Memos*  list_top;
Memos*  selected_memos;
int     x, y, w, h;
int     menu_status;
int     memo_status;
int     key;
int     memo_num;

char* help = "操作方法 j: 下, k: 上, h: 左, l: 右, Enter: 決定, x: ヘルプ, q: 終了";

char*  menus[] = {
    "メモを追加",
    "メモを削除",
    "メモを編集",
    "メモを並び替え",
    "メモを検索",
};

int menu_size = sizeof(menus)/sizeof(char *);

// ??
void show_menu() {
    int i;

    clear();

    // メモを表示
    show_memos_with_select(*selected_memos, memo_status);

    // メニューを表示
    // 一番下にカーソルを合わせる
    y = h-1;
    x = 0;
    move(y, x);

    for(i = 0; i < menu_size; i++) {
        if(i == menu_status) {
            attrset(COLOR_PAIR(0) | A_REVERSE);
            printw(menus[i]);
            attrset(COLOR_PAIR(0));
        } else {
            printw(menus[i]);
        }
        printw(" ");
    }

    printw("  %s", help);

    refresh();
}


// ??
void print_start_window() {
    while (1) {
        // メニューを表示
        show_menu();
        //if(selected_memos->next != NULL)
        
        // Memos* tmp;
        // tmp = &list_top;
        // while(tmp->next != NULL && tmp->memo.title.value != NULL) {
        //     printw("%s->", tmp->memo.title.value);
        //     tmp = tmp->next;
        // }
        // if(tmp->memo.title.value != NULL)
        //     printw("%s->", tmp->memo.title.value);
        // if(selected_memos->prev != NULL)
        //     printw("%s->", selected_memos->prev->memo.title.value);
        // printw("[%s]", selected_memos->memo.title.value);
        // if(selected_memos->next != NULL)
        //     printw("->%s", selected_memos->next->memo.title.value);

        key = getch();
        if (key == 'q') break;
        switch(key) {
            case KEY_UP:
            case 'k':
                if(selected_memos->prev != NULL) {
                    selected_memos = selected_memos->prev;
                    if(memo_status > 0)
                        memo_status -= 1;
                }
                break;
            case KEY_DOWN:
            case 'j':
                if(selected_memos->next != NULL) {
                    selected_memos = selected_memos->next;
                    if(memo_status < MAX_SHOW_MEMOS - 1)
                        memo_status += 1;
                }
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


// Maybe ok
void print_add_memo_window() {
    String title;
    String text;
    Memo   memo;
    char* tmp;

    tmp = malloc(sizeof(char *) * BUFSIZE);

    clear();
    echo();

    printw("メモタイトルを入力してください: ");
    scanw("%s", tmp);
    title = make_str(tmp);
    
    printw("メモの内容を入力してください: ");
    scanw("%s", tmp);
    text = make_str(tmp);

    memo = make_memo(title, text);

    if(list_top->memo.title.value == NULL) {
        add_memo(list_top, memo);
    } else {
        add_memo(selected_memos, memo);
    }

    memo_num += 1;

    free(tmp);

    noecho();
}

void print_remove_memo_window() {
    clear();
    show_memo(selected_memos->memo);
    printw("\nこのメモを削除しますか？(y/n)");
    refresh();

    while(1){
        key = getch();
        if(key == 'y'){
            if(selected_memos->prev == NULL){
                if(selected_memos->next != NULL) {
                    list_top = list_top->next;
                    list_top->prev = NULL;
                } else {

                }
            }
            remove_memo(selected_memos);
            memo_status = 0;
            memo_num    -= 1;
            break;
        } else if(key == 'n'){
            break;
        }
    }
    selected_memos = list_top;
}

void print_edit_memo_window() {
    int   edit_menu_status;
    edit_menu_status = 0;

    while(1) {
        clear();
        show_memo(selected_memos->memo);
        printw("このメモを編集します\n");
        printw("タイトル、テキストのどちらを編集しますか？");

        y = h-1;
        x = 0;
        move(y, x);

        if(edit_menu_status == 0) {
            attrset(COLOR_PAIR(0) | A_REVERSE);
            printw("タイトル");
            attrset(COLOR_PAIR(0));
            printw(" テキスト");
        } else if(edit_menu_status == 1) {
            printw("タイトル ");
            attrset(COLOR_PAIR(0) | A_REVERSE);
            printw("テキスト");
            attrset(COLOR_PAIR(0));
        }

        key = getch();
        if(key == 'q') {
            break;
        } else if(key == '\n') {
            char* tmp;
            tmp = malloc(sizeof(char *) * BUFSIZE);

            clear();
            echo();
            show_memo(selected_memos->memo);

            if(edit_menu_status == 0) {
                printw("タイトルを入力してください: ");
                scanw("%s", tmp);
                set_title(&selected_memos->memo, tmp);
            } else if(edit_menu_status == 1) {
                printw("テキストを入力してください: ");
                scanw("%s", tmp);
                set_text(&selected_memos->memo, tmp);
            }

            noecho();
            break;
        }

        switch(key) {
            case KEY_LEFT:
            case 'h':
                if(edit_menu_status == 1)
                    edit_menu_status = 0;
                break;
            case KEY_RIGHT:
            case 'l':
                if(edit_menu_status == 0)
                    edit_menu_status = 1;
                break;
            default:
                break;
        }
    }
}

void print_sort_memo_window() {
    Memos*  sort_selected_memo;
    int     sort_memo_status;

    sort_selected_memo = selected_memos;
    sort_memo_status = memo_status;
    while (1) {
        // メニューを表示
        clear();
        show_memos_with_select_for_sort(*sort_selected_memo, sort_memo_status, memo_status);
        y = h-1;
        x = 0;
        move(y, x);
        printw("選択したメモの前に、先ほど選択したメモを移動させます。");
        refresh();

        key = getch();
        if (key == '\n') {

            break;
        }
        switch(key) {
            case KEY_UP:
            case 'k':
                if(sort_selected_memo->prev != NULL)
                    sort_selected_memo = sort_selected_memo->prev;
                if(sort_memo_status > 0)
                    sort_memo_status -= 1;
                break;
            case KEY_DOWN:
            case 'j':
                if(sort_selected_memo->next == selected_memos)
                    sort_selected_memo = selected_memos->next;
                else if(sort_selected_memo->next != NULL)
                    sort_selected_memo = sort_selected_memo->next;
                if(sort_memo_status < 3)
                    sort_memo_status += 1;
                break;
        }
    }

}

void print_search_memo_window() {

}

void execute_menu() {
    switch(menu_status) {
        case 0:
            print_add_memo_window();
            break;
        case 1:
            if(memo_num > 0)
                print_remove_memo_window();
            break;
        case 2:
            if(memo_num > 0)
                print_edit_memo_window();
            break;
        case 3:
            if(memo_num > 1)
                print_sort_memo_window();
            break;
        case 4:
            if(memo_num > 0)
                print_search_memo_window();
            break;
    }
}

int main(){
    // 基本はlist_topでメモを管理
    // 初期化処理
    menu_status = 0;
    memo_status = 0;
    memo_num    = 0;
    setlocale(LC_ALL, "");// 日本語
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    use_default_colors();
    noecho();// 入力見えないように
    cbreak();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, h, w);
    curs_set(0);
    clear();

    list_top         = malloc(sizeof(Memos));
    *list_top        = new_memos();
    selected_memos   = list_top;

    // 画面の初期化
    print_start_window();

    endwin();
    return 0;
}