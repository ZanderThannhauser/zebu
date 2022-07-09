
#include <stddef.h>

#include "search_closest.h"
#include "insert_top.h"
#include "insert_node.h"
#include "insert_before.h"
#include "insert_after.h"

avl_node_t *avl_insert_node(avl_tree_t *avltree, avl_node_t *newnode) {
	avl_node_t *node;

	if(!avltree->top)
		return avl_insert_top(avltree, newnode);

	switch(avl_search_closest(avltree, newnode->item, avltree->cmp, &node)) {
		case -1:
			return avl_insert_before(avltree, node, newnode);
		case 1:
			return avl_insert_after(avltree, node, newnode);
	}

	return NULL;
}

