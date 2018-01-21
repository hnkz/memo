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

int edit_memos(Memos* memos, Memo meom) {
    return 0;
}

int swap_memo(Memos* memos1, Memos* memos2) {
    Memos tmp;

    tmp = *memos1;

    memos1->memo.title          = memos2->memo.title;
    memos1->memo.text           = memos2->memo.text;
    memos1->memo.make_time      = memos2->memo.make_time;
    memos1->memo.update_time    = memos2->memo.update_time;
    memos1->memo.make_time_num  = memos2->memo.make_time_num;

    memos2->memo.title          = tmp.memo.title;
    memos2->memo.text           = tmp.memo.text;
    memos2->memo.make_time      = tmp.memo.make_time;
    memos2->memo.update_time    = tmp.memo.update_time;
    memos2->memo.make_time_num  = tmp.memo.make_time_num;

    return 0;
}

Memos* search_memo_by_title(Memos memos, char* title) {
    Memos* ret;
    Memos* tmp;

    ret = NULL;

    while(memos.next != NULL) {
        if(strcmp(memos.memo.title.value, title) == 0) {
            if(ret == NULL){
                tmp         = malloc(sizeof(Memos));
                *tmp        = memos;
                tmp->next   = NULL;
                ret         = tmp;
                ret->prev   = NULL;
            } else {
                tmp->next   = malloc(sizeof(Memos));
                memos.prev  = tmp;
                *tmp->next  = memos;
                tmp         = tmp->next;
                tmp->next   = NULL;
            }
        }

        memos = *memos.next;
    }

    return ret;
}

Memos* search_memo_by_text(Memos memos, char* text) {
    
}

Memos* search_memo_by_date(Memos memos, time_t make_time_num) {
    
}

void show_memos(Memos memos) {
    int i;
    for(i = 0; memos.next != NULL; i++) {
        printw("%s->", memos.memo.title.value);
        //show_memo(memos.memo);
        memos = *memos.next;
    }
    printw("%s", memos.memo.title.value);
    //show_memo(memos.memo);
}

void show_memos_with_select(Memos memos) {
    Memos*  next;
    Memos*  prev;
    Memos*  next_next;
    Memos*  prev_prev;

    next        = memos.next;
    prev        = memos.prev;
    prev_prev   = NULL;
    next_next   = NULL;

    if(prev != NULL) {
        prev_prev = prev->prev;
    }
    if(next != NULL) {
        next_next = next->next;
    }

    if (next != NULL && prev != NULL) {
        show_memo(prev->memo);
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
        show_memo(next->memo);
    } else if (next == NULL && prev != NULL) {
        if(prev_prev != NULL)
            show_memo(prev_prev->memo);
        show_memo(prev->memo);
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
    } else if (prev == NULL && next != NULL) {
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
        show_memo(next->memo);
        if(next_next != NULL)
            show_memo(next_next->memo);
    } else {
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
    }
}

void show_memos_title_with_select(Memos memos) {
    
}

void show_memos_with_select_for_sort(Memos memos, Memos selected_memos) {
    Memos*  next;
    Memos*  prev;
    Memos*  next_next;
    Memos*  prev_prev;

    next        = memos.next;
    prev        = memos.prev;
    prev_prev   = NULL;
    next_next   = NULL;

    if(prev != NULL) {
        if(cmp_memo_by_date(prev->memo, selected_memos.memo) == 0) {
            prev = prev->prev;
        }
        if(prev != NULL)
            prev_prev = prev->prev;
        if(prev_prev != NULL && cmp_memo_by_date(prev_prev->memo, selected_memos.memo) == 0)
            prev_prev = prev_prev->prev;
    }
    if(next != NULL) {
        if(cmp_memo_by_date(next->memo, selected_memos.memo) == 0) {
            next = next->next;
        }
        if(next != NULL)
            next_next = next->next;
        if(next_next != NULL && cmp_memo_by_date(next_next->memo, selected_memos.memo) == 0)
            next_next = next_next->next;
    }

    if (next != NULL && prev != NULL) {
        show_memo(prev->memo);
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
        show_memo(next->memo);
    } else if (next == NULL && prev != NULL) {
        if(prev_prev != NULL)
            show_memo(prev_prev->memo);
        show_memo(prev->memo);
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
    } else if (prev == NULL && next != NULL) {
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
        show_memo(next->memo);
        if(next_next != NULL)
            show_memo(next_next->memo);
    } else {
        attrset(COLOR_PAIR(0)| A_REVERSE);
        show_memo(memos.memo);
        attrset(COLOR_PAIR(0));
    }
}

void free_memos(Memos* memos) {
    free_memo(&memos->memo);
}