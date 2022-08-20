
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void regextree_foreach(
	struct regextree* this,
	void (*runme)(struct regex*))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

