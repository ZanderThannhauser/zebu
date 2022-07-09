
#include "tree_t.h"
#include "node_t.h"

/* Searches for the item in the tree and returns a matching node if found
 * or NULL if not.
 * O(lg n) */
extern avl_node_t *avl_search(const avl_tree_t *, const void *item);

