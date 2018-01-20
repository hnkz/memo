#include <memolib/memo.h>

Memo new_memo() {
    Memo    memo;
    time_t  t;
    char    make_time[64];
    char    update_time[64];

    // メモの時間の更新
    t = time(NULL);
    strftime(make_time, sizeof(make_time), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
    strftime(update_time, sizeof(update_time), "%Y/%m/%d %a %H:%M:%S", localtime(&t));

    memo.title          = new_string();
    memo.text           = new_string();
    memo.make_time      = make_str(make_time);
    memo.update_time    = make_str(update_time);
    memo.make_time_num  = t;

    return memo;
}

Memo make_memo(String title, String text) {
    Memo    memo;
    time_t  t;
    char    update_time[64];

    // update_timeの更新
    memo    = new_memo();
    t       = time(NULL);
    strftime(update_time, sizeof(update_time), "%Y/%m/%d %a %H:%M:%S", localtime(&t));

    memo.title          = title;
    memo.text           = text;
    set_str_value(&(memo.update_time), update_time);

    return memo;
}

int set_title(Memo* memo, char* title) {
    time_t  t;
    char    update_time[64];

    // update_timeの更新
    t = time(NULL);
    strftime(update_time, sizeof(update_time), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
    set_str_value(&(memo->update_time), update_time);

    return set_str_value(&(memo->title), title);
}

int set_text(Memo* memo, char* text) {
    time_t  t;
    char    update_time[64];

    // update_timeの更新
    t = time(NULL);
    strftime(update_time, sizeof(update_time), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
    set_str_value(&(memo->update_time), update_time);

    return set_str_value(&(memo->text), text);
}

void free_memo(Memo* memo) {
    free_str(memo->title);
    free_str(memo->text);
    free_str(memo->make_time);
    free_str(memo->update_time);
}

int cmp_memo_by_title(Memo memo1, Memo memo2) {
    return strcmp(memo1.title.value, memo2.title.value);
}

int cmp_memo_by_date(Memo memo1, Memo memo2) {
    if(memo1.make_time_num == memo2.make_time_num)
        return 0;
    else if(memo1.make_time_num > memo2.make_time_num)
        return 1;
    else 
        return -1;
}

void show_memo(Memo memo) {
    int i;
    int center;
    int count;

    // 1ライン　60文字
    // for(i = 0; i < CHARS_PER_LINE / 2; i++)
    //     printf("--");
    // printf(" タイトル ");
    // for(i = 0; i < CHARS_PER_LINE / 2; i++)
    //     printf("--");
    // printf("\n");

    // タイトル
    printf("\033[1m");
    center = CHARS_PER_LINE - (count_str(memo.title) / 2);
    for(i = 0; i < center; i++)
        printf(" ");
    // for(i = 0; i < memo.title.length; i++) {
    //     // 改行処理
    //     if(count > 50) {
    //         count = 0;
    //         printf("\n");
    //         // センタリング
    //         for(i = 0; i < center; i++)
    //             printf(" ");
    //     }
    //     putchar(memo.title.value[i]);
    //     count++;
    // }
    printf("\033[1m%s\033[0m\n|", memo.title.value);

    // 本文
    for(i = 0; i < CHARS_PER_LINE; i++)
        printf("––");

    printf("|\n|");

    printf(" ");
    printf("%s", memo.text.value);
    count = CHARS_PER_LINE * 2 - (count_str(memo.text) + 1);
    for(i = 0; i < count; i++)
        printf(" ");
    printf("|\n|");

    // 日時
    for(i = 0; i < CHARS_PER_LINE; i++)
        printf("––");
    printf("|\n| 作成: %s 更新: %s", memo.make_time.value, memo.update_time.value);
    count = CHARS_PER_LINE * 2 - (14 + count_str(memo.make_time) + count_str(memo.update_time));
    for(i = 0; i < count; i++)
        printf(" ");
    printf("|\n|");

    // 最後のライン
    for(i = 0; i < CHARS_PER_LINE; i++)
        printf("––");
    printf("|\n\n");
}