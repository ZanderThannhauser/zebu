
#include <stdlib.h>

#include "init_tree.h"
#include "alloc_tree.h"

avl_tree_t *avl_alloc_tree(avl_compare_t cmp, avl_freeitem_t freeitem) {
	return avl_init_tree(malloc(sizeof(avl_tree_t)), cmp, freeitem);
}

