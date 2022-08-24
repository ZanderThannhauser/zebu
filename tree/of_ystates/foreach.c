
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void ystatetree_foreach(
	struct ystatetree* this,
	void (*runme)(struct yacc_state*))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

