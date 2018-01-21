#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <locale.h>

#include <memolib/memos.h>

#define BUFSIZE         64
#define FILE_LINE_CHARS 4096

// ファイル名
char* filename    = "memo.sav";

// ファイル読み込みの際に用いるセパレータ指定子
char* separator   = ",";

// ヘルプ文字列
char* help        = "操作方法 j: 下, k: 上, h: 左, l: 右, Enter: 決定, x: 表示切り替え, q: 終了";

// メニュー 一覧
char* start_menus[]     = {
    "メモを追加",
    "メモを削除",
    "メモを編集",
    "メモを入れ替え",
    "メモを検索",
};

// 検索できる項目
char* search_menus[] = {
    "タイトル",
//    "テキスト",
//    "作成日時",
};

// 検索語のメニュー
char* searched_menus[] = {
//    "メモを削除",
//    "メモを編集",
};

// メニューのサイズ
int start_menu_size      = sizeof(start_menus)/sizeof(char *);

// 検索メニューのサイズ
int search_menu_size     = sizeof(search_menus)/sizeof(char *);

// 検索語メニューのサイズ
int searched_menu_size   = sizeof(searched_menus)/sizeof(char *);

// 初期化処理
void    init();

// スタート画面のメニューを表示
void print_menu(Memos now_memos, char* menus[], int menu_size, char* description, int menu_status);

// 検索画面のメニューを表示
void    print_search_menu(Memos list);

// スタート画面を表示
void    print_start_window();

// メモ追加画面を表示
void    print_add_memo_window();

// メモ編集画面を表示
void    print_edit_memo_window();

// メモ削除画面を表示
void    print_remove_memo_window();

// メモ並び替え画面を表示
void    print_swap_memo_window();

// メモ検索画面を表示
void    print_search_memo_window();

// 選択している操作を実行
void    execute_menu();

// ファイルから読み込んだメモを追加
void    add_memo_for_main(Memo memo);

// ファイルの読み込みとメモの追加
void    read_file_and_add_memo();

// メモをファイルに書き込み
void    save_memo();


// リストのトップを保持
Memos*  list_top;

// 現在のmemosを保持
Memos*  selected_memos;

int     x, y, w, h;
int     start_menu_status;
int     show_mode;
int     key;
int     memo_num;

// ??
void print_menu(Memos now_memos, char* menus[], int menu_size, char* description, int menu_status) {
    int i;

    clear();

    // メモを表示(未実装)
    if(show_mode == 0)
        show_memos_with_select(now_memos);
    if(show_mode == 1)
        show_memos_with_select(now_memos);

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

    printw("  %s", description);

    refresh();
}

// ??
void print_start_window() {
    while (1) {
        // メニューを表示
        print_menu(*selected_memos, start_menus, start_menu_size, help, start_menu_status);

        key = getch();
        if (key == 'q') {
            endwin();
            break;
        }
        switch(key) {
            case KEY_UP:
            case 'k':
                if(selected_memos->prev != NULL) {
                    selected_memos = selected_memos->prev;
                }
                break;
            case KEY_DOWN:
            case 'j':
                if(selected_memos->next != NULL) {
                    selected_memos = selected_memos->next;
                }
                break;
            case KEY_LEFT:
            case 'h':
                if(start_menu_status == 0)
                    start_menu_status = start_menu_size-1;
                else 
                    start_menu_status -= 1;
                break;
            case KEY_RIGHT:
            case 'l':
                if(start_menu_status == start_menu_size-1)
                    start_menu_status = 0;
                else
                    start_menu_status += 1;
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

void print_swap_memo_window() {
    Memos*  swap_selected_memo;

    if(selected_memos->next != NULL)
        swap_selected_memo = selected_memos->next;
    else if(selected_memos->prev != NULL)
        swap_selected_memo = selected_memos->prev;
    while (1) {
        // メニューを表示
        clear();
        show_memos_with_select_for_sort(*swap_selected_memo, *selected_memos);
        y = h-1;
        x = 0;
        move(y, x);
        printw("選択したメモの前に、先ほど選択したメモを移動させます。");
        refresh();

        key = getch();
        if (key == '\n') {
            swap_memo(selected_memos, swap_selected_memo);
            break;
        } else if (key == 'q') {
            break;
        }
        switch(key) {
            case KEY_UP:
            case 'k':
                if(swap_selected_memo->prev != NULL) {
                    swap_selected_memo = swap_selected_memo->prev;
                    if( cmp_memo_by_date(swap_selected_memo->memo, selected_memos->memo) == 0) {
                        if(swap_selected_memo->prev != NULL) {
                            swap_selected_memo = swap_selected_memo->prev;
                        } else {
                            if(swap_selected_memo->next != NULL)
                                swap_selected_memo = swap_selected_memo->next;
                        }
                    }
                }
                break;
            case KEY_DOWN:
            case 'j':
                if(swap_selected_memo->next != NULL) {
                    swap_selected_memo = swap_selected_memo->next;
                    if( cmp_memo_by_date(swap_selected_memo->memo, selected_memos->memo) == 0) {
                        if(swap_selected_memo->next != NULL) {
                            swap_selected_memo = swap_selected_memo->next;
                        } else {
                            if(swap_selected_memo->prev != NULL)
                                swap_selected_memo = swap_selected_memo->prev;
                        }
                    }
                }
                break;
        }
    }

}

void print_search_memo_window() {
    int search_menu_status;
    int i;

    search_menu_status = 0;

    while(1) {
        clear();
        printw("どの項目から検索しますか？");
        y = h-1;
        x = 0;
        move(y, x);

        for(i = 0; i < search_menu_size; i++) {
            if(i == search_menu_status){
                printw(" ");
                attrset(COLOR_PAIR(0) | A_REVERSE);
                printw("%s", search_menus[i]);
                attrset(COLOR_PAIR(0));
            } else {
                printw(" %s", search_menus[i]);
            }
        }

        key = getch();
        if(key == 'q') {
            break;
        } else if(key == '\n') {
            Memos*  search_top;
            char*   tmp_char;

            tmp_char = malloc(sizeof(char *) * BUFSIZE);

            clear();
            echo();
            printw("検索する[ %s ]を入力してください: ", search_menus[search_menu_status]);
            scanw("%s", tmp_char);

            search_top = NULL;
            if(search_menu_status == 0) {
                search_top = search_memo_by_title(*list_top, tmp_char);
            } else if(search_menu_status == 1) {
                search_top = search_memo_by_text(*list_top, tmp_char);
            } else if(search_menu_status == 2) {
                search_top = search_memo_by_date(*list_top, atoi(tmp_char));
            }

            if(search_top != NULL) {
                Memos* searched_selected_memos;

                searched_selected_memos = search_top;
                search_menu_status = 0;
                while (1) {
                    // メニューを表示
                    print_menu(*searched_selected_memos, searched_menus, searched_menu_size, help, search_menu_status);

                    key = getch();
                    if (key == 'q') {
                        break;
                    }
                    switch(key) {
                        case KEY_UP:
                        case 'k':
                            if(searched_selected_memos->prev != NULL) {
                                searched_selected_memos = searched_selected_memos->prev;
                            }
                            break;
                        case KEY_DOWN:
                        case 'j':
                            if(searched_selected_memos->next != NULL) {
                                searched_selected_memos = searched_selected_memos->next;
                            }
                            break;
                        case KEY_LEFT:
                        case 'h':
                            if(search_menu_status == 0)
                                search_menu_status = searched_menu_size-1;
                            else 
                                search_menu_status -= 1;
                            break;
                        case KEY_RIGHT:
                        case 'l':
                            if(search_menu_status == searched_menu_size-1)
                                search_menu_status = 0;
                            else
                                search_menu_status += 1;
                            break;
                        case '\n':
                            execute_menu();
                            break;
                        default:

                            break;
                    }
                }
            }

            free(tmp_char);
            noecho();

            break;
        }

        switch(key) {
            case KEY_LEFT:
            case 'h':
                if(search_menu_status > 0)
                    search_menu_status -= 1;
                break;
            case KEY_RIGHT:
            case 'l':
                if(search_menu_status < 2)
                    search_menu_status += 1;
                break;
            default:
                break;
        }
    }
}

void execute_menu() {
    switch(start_menu_status) {
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
                print_swap_memo_window();
            break;
        case 4:
            if(memo_num > 0)
                print_search_memo_window();
            break;
    }
    save_memo();
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

    // 初期化処理(変数初期化、curses、ファイル読み込み)
    init();

    // 画面の初期化
    print_start_window();

    return 0;
}

void init() {
    start_menu_status   = 0;
    memo_num            = 0;
    show_mode           = 0;

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

    read_file_and_add_memo();
}

void read_file_and_add_memo() {
    FILE* fp;

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

            // add_memo_for_mainはnextにメモを追加するため
            if(selected_memos->next != NULL)
                selected_memos = selected_memos->next;
        }
        fclose(fp);
        selected_memos = list_top;
    }
}

void save_memo() {
    FILE*   fp;
    Memos   tmp;
    String  s;

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