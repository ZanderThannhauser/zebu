
#include <stdlib.h>

#include <debug.h>

#include "free_nodes.h"
#include "free_tree.h"

/*
 * avl_free_tree:
 * Free all memory used by this tree.  If freeitem is not NULL, then
 * it is assumed to be a destructor for the items referenced in the avl_
 * tree, and they are deleted as well.
 */
void avl_free_tree(avl_tree_t *avltree)
{
	ENTER;
	
	if (avltree)
	{
		avl_free_nodes(avltree);
		
		#ifdef WITH_ARENAS
		arena_dealloc(avltree->arena, avltree);
		#else
		free(avltree);
		#endif
	}
	
	EXIT;
}

