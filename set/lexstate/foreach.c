
#include <debug.h>

#include "struct.h"
#include "foreach.h"

void lexstateset_foreach(
	struct lexstateset* this,
	void (*runme)(struct lex_state*))
{
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
		runme(node->item);
}

