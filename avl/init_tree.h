
#include "tree_t.h"

/* Initializes a new tree for elements that will be ordered using
 * the supplied strcmp()-like function.
 * Returns the value of avltree (even if it's NULL).
 * O(1) */

avl_tree_t *avl_init_tree(
	avl_tree_t *rc,
	avl_compare_t cmp,
	avl_freeitem_t freeitem);
