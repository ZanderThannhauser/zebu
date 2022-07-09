
#include <stddef.h>

#include "clear_node.h"

void avl_clear_node(avl_node_t *newnode) {
	newnode->left = newnode->right = NULL;
	newnode->count = 1;
	newnode->depth = 1;
}

