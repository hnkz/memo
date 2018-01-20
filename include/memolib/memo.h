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

// メモ同士を比べる
int     cmp_memo_by_title(Memo memo1, Memo memo2);

// メモを表示　色々と改良が必要
void    show_memo(Memo memo);