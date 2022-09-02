
#include <stddef.h>

#include "search_closest.h"

int avl_search_closest(const avl_tree_t *avltree, const void *item, avl_compare_t cmp, avl_node_t **avlnode) {
	avl_node_t *node;
	int c;
	
	if (!avlnode)
		avlnode = &node;
	
	node = avltree->top;
	
	if (!node)
		return *avlnode = NULL, 0;
	
	for (;;) {
		c = cmp(item, node->item);
		
		if(c < 0) {
			if(node->left)
				node = node->left;
			else
				return *avlnode = node, -1;
		} else if(c > 0) {
			if(node->right)
				node = node->right;
			else
				return *avlnode = node, 1;
		} else {
			return *avlnode = node, 0;
		}
	}
}

