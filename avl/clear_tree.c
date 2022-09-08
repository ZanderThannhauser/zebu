
#include <stddef.h>

#include "clear_tree.h"

void avl_clear_tree(avl_tree_t *avltree)
{
	avltree->top = avltree->head = avltree->tail = NULL;
}

