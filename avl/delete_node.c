
#include <stddef.h>
#include <stdlib.h>

#include <debug.h>

#include <arena/dealloc.h>

#include "unlink_node.h"
#include "delete_node.h"

void *avl_delete_node(
	avl_tree_t *avltree,
	avl_node_t *avlnode)
{
	ENTER;
	
	void *item = NULL;
	
	if (avlnode)
	{
		item = avlnode->item;
		
		avl_unlink_node(avltree, avlnode);
		
		if (avltree->freeitem)
		{
			avltree->freeitem(item);
		}
		
		#ifdef WITH_ARENAS
		arena_dealloc(avltree->arena, avlnode);
		#else
		free(avlnode);
		#endif
	}
	
	EXIT;
	return item;
}
