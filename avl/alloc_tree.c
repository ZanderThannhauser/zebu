
#include <stdlib.h>

#include <debug.h>

#include <arena/malloc.h>

#include "init_tree.h"
#include "alloc_tree.h"

avl_tree_t* avl_alloc_tree(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	avl_compare_t cmp,
	avl_freeitem_t freeitem)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	avl_tree_t* tree = arena_malloc(arena, sizeof(avl_tree_t));
	#else
	avl_tree_t* tree = malloc(sizeof(avl_tree_t));
	#endif
	
	#ifdef WITH_ARENAS
	avl_init_tree(tree, arena, cmp, freeitem);
	#else
	avl_init_tree(tree, cmp, freeitem);
	#endif
	
	EXIT;
	return tree;
}

