
#include <stddef.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <avl/insert.h>
#include <avl/alloc_tree.h>

#include "struct.h"
#include "clone.h"

struct lexstateset* lexstateset_clone(
	const struct lexstateset* cloneme)
{
	ENTER;
	
	struct avl_tree_t* tree = avl_alloc_tree(cloneme->tree->cmp, NULL);
	
	for (struct avl_node_t* node = cloneme->tree->head; node; node = node->next)
	{
		avl_insert(tree, node->item);
	}
	
	struct lexstateset* new = smalloc(sizeof(*new));
	
	new->tree = tree;
	new->len = cloneme->len;
	
	EXIT;
	return new;
}
