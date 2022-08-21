
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "clone.h"

struct regextree* regextree_clone(struct regextree* this)
{
	TODO;
	
	#if 0
	struct avl_tree_t* tree = new_avl_tree(this->tree->cmp, this->tree->freeitem);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		safe_avl_insert(tree, node->item);
	}
	
	struct regextree* new = smalloc(sizeof(*new));
	
	new->tree = tree;
	
	new->n = this->n;
	
	return new;
	#endif
}

