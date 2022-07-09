
#include <stddef.h>

#include "search_closest.h"
#include "search.h"

/*
 * avl_search:
 * Return a pointer to a node with the given item in the tree.
 * If no such item is in the tree, then NULL is returned.
 */
avl_node_t *avl_search(const avl_tree_t *avltree, const void *item) {
	avl_node_t *node;
	return avl_search_closest(avltree, item, avltree->cmp, &node) ? NULL : node;
}

