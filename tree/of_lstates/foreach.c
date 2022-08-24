
#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "foreach.h"

void lstatetree_foreach(
	struct lstatetree* this,
	void (*runme)(struct lex_state*))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

