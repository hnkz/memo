#include <memolib/memos.h>
#include <curses.h>

Memos new_memos() {
    Memos memos;

    memos.memo      = new_memo();
    memos.next      = NULL;
    memos.prev      = NULL;

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

    // 初メモだったら
    if(memos->memo.title.value == NULL) {
        memos->memo = memo;
        return 0;
    }

    tmp         = malloc(sizeof(Memos));
    *tmp        = new_memos();
    tmp->memo   = memo;

    if(memos->next == NULL) {
        memos->next = tmp;
        tmp->prev = memos;
    } else {
        tmp->prev           = memos;
        tmp->next           = memos->next;
        memos->next->prev   = tmp;
        memos->next         = tmp;
    }

    return 0;
}

int remove_memo(Memos* memos) {
    Memos* tmp;

    // if(memos->prev != NULL)
    //     printw("%s->", memos->prev->memo.title.value);
    // printw("[%s]", memos->memo.title.value);
    // if(memos->next != NULL)
    //     printw("->%s", memos->next->memo.title.value);

    tmp = memos;
    if(tmp->prev != NULL) {
        if(tmp->next != NULL) {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
        } else {
            tmp->prev->next = NULL;
        }
        free(tmp);
    } else {
        if(memos->next != NULL) {
            memos       = memos->next;
            memos->prev = NULL;
            free(tmp);
        } else {
            *memos = new_memos();
        }
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
    for(i = 0; i < MAX_SHOW_MEMOS && memos.next != NULL; i++) {
        show_memo(memos.memo);
        memos = *memos.next;
    }
    show_memo(memos.memo);
}

void show_memos_with_select(Memos memos, int selected) {
    if(memos.memo.title.value != NULL){
        if(selected == 0) {
            attrset(COLOR_PAIR(0)| A_REVERSE);
            show_memo(memos.memo);
            attrset(COLOR_PAIR(0));
            if(memos.next != NULL){
                show_memo(memos.next->memo);
                if(memos.next->next != NULL)
                    show_memo(memos.next->next->memo);
            }
        } else if(selected == 1) {
            if(memos.prev != NULL)
                show_memo(memos.prev->memo);
            attrset(COLOR_PAIR(0)| A_REVERSE);
            show_memo(memos.memo);
            attrset(COLOR_PAIR(0));
            if(memos.next != NULL)
                show_memo(memos.next->memo);
        } else if(selected == 2) {
            if(memos.prev != NULL){
                if(memos.prev->prev != NULL)
                    show_memo(memos.prev->prev->memo);
                show_memo(memos.prev->memo);
            }
            attrset(COLOR_PAIR(0)| A_REVERSE);
            show_memo(memos.memo);
            attrset(COLOR_PAIR(0));
        }
    }
}

void show_memos_with_select_for_sort(Memos memos, int will_select, int selected) {

}

void free_memos(Memos* memos) {
    free_memo(&memos->memo);
}