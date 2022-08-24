
#include <stdlib.h>
#include <debug.h>

#include <avl/tree_t.h>
#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "struct.h"
#include "clone.h"

struct ystatetree* ystatetree_clone(
	#ifdef WITH_ARENAS
	struct memory_arena* arena,
	#endif
	const struct ystatetree* this)
{
	ENTER;
	
	#ifdef WITH_ARENAS
	struct avl_tree_t* tree = avl_alloc_tree(arena, this->tree->cmp, this->tree->freeitem);
	#else
	struct avl_tree_t* tree = avl_alloc_tree(this->tree->cmp, this->tree->freeitem);
	#endif
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		avl_insert(tree, node->item);
	}
	
	#ifdef WITH_ARENAS
	struct ystatetree* new = arena_malloc(arena, sizeof(*new));
	#else
	struct ystatetree* new = malloc(sizeof(*new));
	#endif
	
	new->tree = tree;
	
	new->n = this->n;
	
	#ifdef WITH_ARENAS
	new->arena = arena;
	#endif
	
	EXIT;
	return new;
}














