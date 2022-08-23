
#include <errno.h>
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>
#include <arena/dealloc.h>

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
	struct memory_arena* arena;
	ENTER;
	
	arena = avltree->arena;
	
	newnode = avl_init_node(arena_malloc(arena, sizeof(avl_node_t)), item);
	
	if (newnode)
	{
		if (avl_insert_node(avltree, newnode))
		{
			EXIT;
			return newnode;
		}
		
		arena_dealloc(arena, newnode);
		
		errno = EEXIST;
	}
	
	EXIT;
	return NULL;
}

