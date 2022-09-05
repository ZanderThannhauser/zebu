
#include <stdlib.h>

#include <memory/smalloc.h>

#include "init_tree.h"
#include "alloc_tree.h"

avl_tree_t* avl_alloc_tree(
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	avl_tree_t* tree = smalloc(sizeof(avl_tree_t));
	avl_init_tree(tree, cmp, freeitem);
	return tree;
}

