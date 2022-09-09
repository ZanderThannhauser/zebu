
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void unsignedsetset_foreach(
	struct unsignedsetset* this,
	void (*runme)(struct unsignedset*))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

