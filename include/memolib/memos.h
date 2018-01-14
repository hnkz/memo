#include <memolib/memo.h>

typedef struct __Node {
    Memo    memo;
    struct __Node*   right;
    struct __Node*   left;
} Node;
