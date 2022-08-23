
#include <stddef.h>

#include <debug.h>

#include "clear_tree.h"

void avl_clear_tree(avl_tree_t *avltree)
{
	ENTER;
	avltree->top = avltree->head = avltree->tail = NULL;
	EXIT;
}

