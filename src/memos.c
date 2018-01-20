#include <memolib/memos.h>
#include <curses.h>

Memos new_memos() {
    Memos memos;

    memos.memo      = new_memo();
    memos.next      = NULL;
    memos.before    = NULL;

    return memos;
}

MemoStack new_memo_stack() {
    MemoStack stack;

    stack.num = 0;

    return stack;
}

int push_memo(MemoStack* stack, Memo memo) {
    stack->memo[(stack->num)++] = memo;

    return 0;
}

Memo pop_memo(MemoStack* stack) {
    return stack->memo[--(stack->num)];
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
    int i;
    for(i = 0; i < 3 && memos.next != NULL; i++) {
        show_memo(memos.memo);
        memos = *memos.next;
    }
    show_memo(memos.memo);
}

void show_memos_with_select(Memos memos, int num) {
    int i;
    Memos*      next_memos;
    Memos*      before_memos;
    MemoStack   stack;

    next_memos      = memos.next;
    before_memos    = memos.before;
    stack           = new_memo_stack();

    if(before_memos != NULL) {
        for(i = 0; i < num - 1 && before_memos->before != NULL; i++) {
            push_memo(&stack, before_memos->memo);
            before_memos = before_memos->before;
        }
        push_memo(&stack, before_memos->memo);

        for(i = stack.num; i > 0; i--) {
            show_memo(pop_memo(&stack));
        }
    }
    if(memos.memo.title.value != NULL) {
        attrset(COLOR_PAIR(1));
        show_memo(memos.memo);
        attrset(COLOR_PAIR(2));
    }
    if(next_memos != NULL) {
        for(i = 0; i < MAX_SHOW_MEMOS - num - 1 && next_memos->next != NULL; i++) {
            show_memo(next_memos->memo);
            next_memos = next_memos->next;
        }
        show_memo(next_memos->memo);
    }
}