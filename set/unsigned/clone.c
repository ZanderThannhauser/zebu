
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include "struct.h"
#include "clone.h"

struct unsignedset* unsignedset_clone(
	const struct unsignedset* other)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(other->tree->cmp, free);
	
	for (struct avl_node_t* node = other->tree->head; node; node = node->next)
	{
		unsigned *ele = node->item;
		
		unsigned *copy = smalloc(sizeof(*copy));
		
		*copy = *ele;
		
		avl_insert(tree, copy);
	}
	
	struct unsignedset* new = smalloc(sizeof(*new));
	
	new->tree = tree;
	new->refcount = 1;
	
	EXIT;
	return new;
}

