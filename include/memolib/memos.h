#include <memolib/memo.h>

typedef struct __Node {
    Memo            memo;
    struct __Node*  parent;
    struct __Node*  right;
    struct __Node*  left;
} Node;

// 新しいノードを作成（使わないで）
Node new_node();

// メモからノードを作成
Node make_node_by_memo(Memo memo);

// ノードを追加
Node add_node(Node tree, Node node);

// ノードの削除
Node remove_node(Node tree, String str);


// ノードの検索（文字列から）
Node search_node(Node tree, String str);