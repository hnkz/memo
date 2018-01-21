#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memolib/string.h>

#define CHARS_PER_LINE 50

typedef struct {
    String  title;
    String  text;
    String  make_time;
    String  update_time;
    time_t  make_time_num;
} Memo;

// メモのインスタンス化的な（使わないでね）
Memo    new_memo();

// メモを作成
Memo    make_memo(String title, String text);

// メモのタイトルをセット
int     set_title(Memo* memo, char* title);

// メモのテキストをセット
int     set_text(Memo* memo, char* text);

// メモのメモリ領域を解放
void    free_memo(Memo* memo);

// メモ同士を比べる(タイトルで)
int     cmp_memo_by_title(Memo memo1, Memo memo2);

// メモ同士を比べる(日時で)
int     cmp_memo_by_date(Memo memo1, Memo memo2);

// メモを表示　色々と改良が必要
void    show_memo(Memo memo);

// 保存用のメモを返す
String  ret_memo_for_save(Memo memo);