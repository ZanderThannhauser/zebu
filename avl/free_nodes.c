
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "clear_tree.h"
#include "free_nodes.h"

void avl_free_nodes(avl_tree_t *avltree)
{
	avl_node_t *node, *next;
	avl_freeitem_t freeitem;
	struct memory_arena* arena;
	ENTER;
	
	freeitem = avltree->freeitem;
	
	arena = avltree->arena;
	
	for (node = avltree->head; node; node = next)
	{
		next = node->next;
		
		if (freeitem)
		{
			freeitem(node->item);
		}
		
		arena_dealloc(arena, node);
	}
	
	avl_clear_tree(avltree);
	
	EXIT;
}

