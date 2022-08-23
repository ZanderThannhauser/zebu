
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "clear_tree.h"
#include "free_nodes.h"

void avl_free_nodes(avl_tree_t *avltree)
{
	avl_node_t *node, *next;
	avl_freeitem_t freeitem;
	ENTER;
	
	freeitem = avltree->freeitem;
	
	for (node = avltree->head; node; node = next)
	{
		next = node->next;
		
		if (freeitem)
		{
			freeitem(node->item);
		}
		
		#ifdef WITH_ARENAS
		arena_dealloc(avltree->arena, node);
		#else
		free(node);
		#endif
	}
	
	avl_clear_tree(avltree);
	
	EXIT;
}

