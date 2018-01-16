#include <memolib/memo.h>

typedef struct __Node {
    Memo            memo;
    struct __Node*  parent;
    struct __Node*  right;
    struct __Node*  left;
} Node;

Node new_node();
Node make_node_by_memo(Memo memo);
Node add_node(Node tree, Node node);
Node remove_node(Node tree, String str);
