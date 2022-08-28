
#include <debug.h>

#include "struct.h"
#include "clone.h"

struct regexset* regexset_clone(const struct regexset* this)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(this->tree->cmp, NULL);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct regex* ele = node->item;
		avl_insert(tree, ele);
	}
	
	struct regexset* new = smalloc(sizeof(*new));
	
	new->n = this->n;
	new->tree = tree;
	
	EXIT;
	return new;
}

