#include <memolib/memos.h>

Memos new_memos() {
    Memos memos;

    memos.memo      = new_memo();
    memos.next      = NULL;
    memos.before    = NULL;

    return memos;
}

int add_memo(Memos* memos, Memo memo) {
    Memos* tmp;

    // メモがまだ一つもなかったら
    if(memos->memo.title.value == NULL) {
        memos->memo = memo;
        return 0;
    }

    // 日付順で追加
    // if(cmp_memo_by_date(memos.memo, memo) < 0) {
    //     if(memos->next == NULL) {
    //         tmp         = malloc(sizeof(Memos));
    //         *tmp        = new_memos();
    //         tmp->memo   = memo;

    //         memos->before   = tmp;
    //         tmp->next       = memos;
    //     } else {
    //         add_memo(memos->next, memo);
    //     }
    // } else if (cmp_memo_by_date(memos.memo, memo) >= 0) {
    //     if(memos->next == NULL) {

    //     }
    // }

    if(memos->next == NULL) {    
        tmp         = malloc(sizeof(Memos));
        *tmp        = new_memos();
        tmp->memo   = memo;

        memos->next = tmp;
        tmp->before = memos;
    } else {
        add_memo(memos->next, memo);
    }

    return 0;
}

int remove_memo_by_title(Memos* memos, Memo memo) {
    
    if(cmp_memo_by_title(memos->memo, memo) == 0){
        memos->before->next = memos->next;
        memos->next->before = memos->before;
    } else {
        if(memos->next == NULL)
            return 1;
        remove_memo_by_title(memos->next, memo);
    }
    return 0;
}

int edit_memo(Memos* memos, Memo meom) {
    return 0;
}

int sort_memo_by_date(Memos* memos) {
    return 0;
}

int sort_memo_by_title(Memos* memo) {
    return 0;
}

void show_memos(Memos memos) {
    do
    {
        show_memo(memos.memo);
        memos = *memos.next;
    } while (memos.next != NULL);
    show_memo(memos.memo);
}