
#include <debug.h>

#include "struct.h"
#include "head.h"

unsigned unsignedset_head(const struct unsignedset* this)
{
	struct avl_node_t* node = this->tree->head;
	assert(node);
	return *(unsigned*) node->item;
}

