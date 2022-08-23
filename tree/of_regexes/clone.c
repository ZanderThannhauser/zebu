
#include <debug.h>

#include <avl/tree_t.h>
#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include <arena/malloc.h>

#include "struct.h"
#include "clone.h"

struct regextree* regextree_clone(
	struct regextree* this,
	struct memory_arena* arena)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(arena, this->tree->cmp, this->tree->freeitem);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		avl_insert(tree, node->item);
	}
	
	struct regextree* new = arena_malloc(arena, sizeof(*new));
	
	new->tree = tree;
	
	new->n = this->n;
	
	new->arena = arena;
	
	EXIT;
	return new;
}

