#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <locale.h>

#include <memolib/memos.h>

#define BUFSIZE         64
#define FILE_LINE_CHARS 4096

// スタート画面のメニューを表示
void    show_start_menu();

// スタート画面を表示
void    print_start_window();

// 選択している操作を実行
void    execute_menu();

// メモをファイルにセーブ
void    save_memo();

// ファイルから読み込んだメモを追加
void    add_memo_for_main(Memo memo);

Memos*  list_top;
Memos*  selected_memos;
FILE*   fp;

int     x, y, w, h;
int     menu_status;
int     memo_status;
int     show_mode;
int     key;
int     memo_num;

char* filename  = "memo.sav";
char* separator = ",";
char* help      = "操作方法 j: 下, k: 上, h: 左, l: 右, Enter: 決定, x: 表示切り替え, q: 終了";
char* menus[]   = {
    "メモを追加",
    "メモを削除",
    "メモを編集",
    "メモを入れ替え",
    "メモを検索",
};

int menu_size = sizeof(menus)/sizeof(char *);

// ??
void show_menu() {
    int i;

    clear();

    // メモを表示(未実装)
    if(show_mode == 0)
        show_memos_with_select(*selected_memos, memo_status);
    if(show_mode == 1)
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

        key = getch();
        if (key == 'q') {
            break;
        }
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
                if(show_mode == 0) {
                    show_mode = 1;
                } else if(show_mode == 1) {
                    show_mode = 0;
                }
                break;
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

    // メモの追加
    add_memo_for_main(memo);

    // メモの保存
    save_memo();

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
                }
            }
            remove_memo(selected_memos);

            memo_status = 0;
            memo_num    -= 1;

            // メモの保存
            save_memo();
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

    if(selected_memos->next != NULL)
        sort_selected_memo = selected_memos->next;
    else if(selected_memos->prev != NULL)
        sort_selected_memo = selected_memos->prev;
    sort_memo_status = memo_status;
    while (1) {
        // メニューを表示
        clear();
        show_memos_with_select_for_sort(*sort_selected_memo, *selected_memos);
        y = h-1;
        x = 0;
        move(y, x);
        printw("選択したメモの前に、先ほど選択したメモを移動させます。");
        refresh();

        key = getch();
        if (key == '\n') {
            swap_memo(selected_memos, sort_selected_memo);
            save_memo();
            break;
        } else if (key == 'q') {
            break;
        }
        switch(key) {
            case KEY_UP:
            case 'k':
                if(sort_selected_memo->prev != NULL) {
                    sort_selected_memo = sort_selected_memo->prev;
                    if( cmp_memo_by_date(sort_selected_memo->memo, selected_memos->memo) != 0) {
                        if(sort_memo_status > 0)
                            sort_memo_status -= 1;
                    } else {
                        if(sort_selected_memo->prev != NULL) {
                            sort_selected_memo = sort_selected_memo->prev;
                            if(sort_memo_status > 0)
                                sort_memo_status -= 2;
                        } else {
                            if(sort_selected_memo->next != NULL)
                                sort_selected_memo = sort_selected_memo->next;
                        }
                    }
                }
                break;
            case KEY_DOWN:
            case 'j':
                if(sort_selected_memo->next != NULL) {
                    sort_selected_memo = sort_selected_memo->next;
                    if( cmp_memo_by_date(sort_selected_memo->memo, selected_memos->memo) != 0) {
                        if(sort_memo_status < MAX_SHOW_MEMOS - 1)
                            sort_memo_status += 1;
                    } else {
                        if(sort_selected_memo->next != NULL) {
                            sort_selected_memo = sort_selected_memo->next;
                            if(sort_memo_status < MAX_SHOW_MEMOS - 1)
                                sort_memo_status += 2;
                        } else {
                            if(sort_selected_memo->prev != NULL)
                                sort_selected_memo = sort_selected_memo->prev;
                        }
                    }
                }
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

void save_memo() {
    Memos tmp;
    String s;

    fp = fopen(filename, "w");
    if(fp == NULL) {
        return;
    }

    tmp = *list_top;
    while(tmp.next != NULL) {
        s = ret_memo_for_save(tmp.memo);
        fprintf(fp, "%s", s.value);
        tmp = *(tmp.next);
    } 
    if(tmp.memo.title.value != NULL) {
        s = ret_memo_for_save(tmp.memo);
        fprintf(fp, "%s", s.value);
    }

    fclose(fp);
    free_str(s);
}

void add_memo_for_main(Memo memo) {
     if(list_top->memo.title.value == NULL) {
         add_memo(list_top, memo);
     } else {
         add_memo(selected_memos, memo);
     }

     // メモのカウント
     memo_num += 1;
}

int main(){
    // 基本はlist_topでメモを管理
    // 初期化処理
    menu_status = 0;
    memo_status = 0;
    memo_num    = 0;
    show_mode   = 0;
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

    // ファイル読み込み処理
    fp = fopen(filename, "r");
    if(fp != NULL) {
        char    line[FILE_LINE_CHARS];
        char*   tok;
        Memo    memo;

        while(fgets(line, FILE_LINE_CHARS, fp) != NULL) {
            // タイトル
            tok     = strtok(line, separator);
            memo.title   = make_str(tok);

            // テキスト
            tok     = strtok(NULL, separator);
            memo.text    = make_str(tok);
            
            // 作成日時
            tok         = strtok(NULL, separator);
            memo.make_time   = make_str(tok);

            // 更新日時
            tok         = strtok(NULL, separator);
            memo.update_time = make_str(tok);

            // 作成日時num
            tok     = strtok(NULL, separator);
            memo.make_time_num = (time_t)atoi(tok);
            add_memo_for_main(memo);
            if(selected_memos->next != NULL)
                selected_memos = selected_memos->next;
        }
        fclose(fp);
        selected_memos = list_top;
    }

    // 画面の初期化
    print_start_window();

    endwin();
    return 0;
}