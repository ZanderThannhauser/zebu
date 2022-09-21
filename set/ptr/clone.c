
#include <debug.h>

#include "struct.h"
#include "clone.h"

struct ptrset* ptrset_clone(const struct ptrset* this)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(this->tree->cmp, NULL);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct regex* ele = node->item;
		
		avl_insert(tree, ele);
	}
	
	struct ptrset* new = smalloc(sizeof(*new));
	
	new->refcount = 1;
	new->tree = tree;
	
	EXIT;
	return new;
}

