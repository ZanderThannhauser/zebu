
#include <assert.h>

#include <debug.h>

#include <avl/tree_t.h>

#include "struct.h"
#include "enumerate.h"

void gegextree_enumerate(
	const struct gegextree* this,
	void (*runme)(unsigned, struct gegex*))
{
	struct avl_node_t* node;
	ENTER;
	
	node = this->tree->head;
	
	for (unsigned i = 0, n = this->n; i < n; i++, node = node->next)
	{
		runme(i, node->item);
	}
	
	assert(!node);
	
	EXIT;
}

