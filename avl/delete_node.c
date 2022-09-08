
#include <stddef.h>
#include <stdlib.h>

#include "unlink_node.h"
#include "delete_node.h"

void *avl_delete_node(
	avl_tree_t *avltree,
	avl_node_t *avlnode)
{
	void *item = NULL;
	
	if (avlnode)
	{
		item = avlnode->item;
		
		avl_unlink_node(avltree, avlnode);
		
		if (avltree->freeitem)
		{
			avltree->freeitem(item);
		}
		
		free(avlnode);
	}
	
	return item;
}
