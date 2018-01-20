#include <memolib/memo.h>

typedef struct __Memos {
    Memo  memo;
    struct __Memos* next;
    struct __Memos* before;
} Memos;

// 新しいメモを作成
Memos new_memos();

// メモを追加
int   add_memo(Memos* memos, Memo memo);

// メモを削除
int   remove_memo_by_title(Memos* memos, Memo memo);

// メモを変更
int   edit_memo(Memos* memos, Memo memo);

// メモを日時でソート
int   sort_memo_by_date(Memos* memos);

// メモをタイトルでソート
int   sort_memo_by_title(Memos* memos);

// メモを表示
void  show_memos(Memos memos);