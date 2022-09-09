
#include <stddef.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/alloc_tree.h>
#include <avl/insert.h>

#include "struct.h"
#include "clone.h"

struct gegexset* gegexset_clone(
	const struct gegexset* this)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(this->tree->cmp, NULL);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		avl_insert(tree, node->item);
	}
	
	struct gegexset* new = smalloc(sizeof(*new));
	
	new->tree = tree;
	new->n = this->n;
	
	EXIT;
	return new;
}

