
#include <errno.h>
#include <stdlib.h>

#include <memory/smalloc.h>

#include "tree_t.h"
#include "insert.h"

#include "init_node.h"
#include "insert_node.h"

/*
 * avl_insert:
 * Create a new node and insert an item there.
 * Returns the new node on success or NULL if no memory could be allocated.
 */
avl_node_t *avl_insert(avl_tree_t *avltree, void *item)
{
	avl_node_t *newnode;
	
	newnode = avl_init_node(smalloc(sizeof(avl_node_t)), item);
	
	if (newnode)
	{
		if (avl_insert_node(avltree, newnode))
		{
			return newnode;
		}
		
		free(newnode);
		
		errno = EEXIST;
	}
	
	return NULL;
}















