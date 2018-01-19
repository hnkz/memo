#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char*   value;
    int     length;
} String;

// 新しいストリングを作成（基本はmake_strのみを使う)
String  new_string();
// Stringから文字列をゲットする
char*   get_str_value(String str);
// Stringに文字列をセットする
int     set_str_value(String* str, char* char_str);
// Stringをchar*から作成する
String  make_str(char *value);
// String二つを連結する
String  link_str(String str1, String str2);
// Stringのメモリ領域を解放する
void    free_str(String str);
// 表示される文字数をカウント
int     count_str(String str);