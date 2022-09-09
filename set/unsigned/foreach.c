
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void unsignedset_foreach(
	const struct unsignedset* this,
	void (*runme)(unsigned))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		runme(*(unsigned*) node->item);
	}
}

