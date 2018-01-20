#include <memolib/memo.h>

#define MAX_SHOW_MEMOS 4
#define MAX_MEMO_STACK 1024

typedef struct __Memos {
    Memo  memo;
    struct __Memos* next;
    struct __Memos* before;
} Memos;

typedef struct {
  Memo memo[MAX_MEMO_STACK];
  int num;
} MemoStack;

// 新しいメモを作成
Memos new_memos();

// メモのスタックを作成
MemoStack new_memo_stack();

// メモスタックにプッシュ
int push_memo(MemoStack* stack, Memo memo);


// メモスタックをポップ
Memo pop_memo(MemoStack* stack);

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

// メモをタイトルで検索 複数場合は線形リストで
Memos search_memo_by_title(Memos* memos);

// メモを日付で検索
Memos search_memo_by_date(Memos* memos);

// メモを表示
void  show_memos(Memos memos);

// 選択状態でメモを表示
void  show_memos_with_select(Memos memos, int num);