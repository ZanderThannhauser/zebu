
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "init_tree.h"
#include "alloc_tree.h"

avl_tree_t* avl_alloc_tree(
	struct memory_arena* arena,
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	ENTER;
	
	avl_tree_t* tree = arena_malloc(arena, sizeof(avl_tree_t));
	
	avl_init_tree(tree, arena, cmp, freeitem);
	
	EXIT;
	return tree;
}

