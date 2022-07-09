
#include "init_node.h"

avl_node_t *avl_init_node(avl_node_t *newnode, void *item) {
	if(newnode) {
/*		avl_clear_node(newnode); */
		newnode->item = item;
	}
	return newnode;
}

