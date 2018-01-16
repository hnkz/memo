#include <memolib/memos.h>

Node new_node() {
    Node node;

    node.memo   = new_memo();
    node.parent = NULL;
    node.right  = NULL;
    node.left   = NULL;

    return node;
}

Node make_node_by_memo(Memo memo) {
    Node node;

    node = new_node();
    node.memo = memo;

    return node;
}

Node add_node(Node tree, Node node) {
    Node result;

    return result;
}

Node remove_node(Node tree, String str) {
    Node result;

    return result;
}
