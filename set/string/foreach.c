
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void stringset_foreach(
	const struct stringset* this,
	void (*runme)(struct string* element))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

