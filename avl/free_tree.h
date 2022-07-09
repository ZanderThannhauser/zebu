
#include "tree_t.h"

/* Frees the entire tree efficiently. Nodes will be free()d.
 * If the tree's freeitem is not NULL it will be invoked on every item.
 * O(n) */
extern void avl_free_tree(avl_tree_t *);

