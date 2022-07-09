
#include "tree_t.h"

/* Free()s all nodes in the tree but leaves the tree itself.
 * If the tree's freeitem is not NULL it will be invoked on every item.
 * O(n) */
extern void avl_free_nodes(avl_tree_t *);

