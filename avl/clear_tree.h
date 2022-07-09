
#include "tree_t.h"

/* Reinitializes the tree structure for reuse. Nothing is free()d.
 * Compare and freeitem functions are left alone.
 * O(1) */
extern void avl_clear_tree(avl_tree_t *);

