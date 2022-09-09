
#include <debug.h>

#include <avl/free_nodes.h>

#include "struct.h"
#include "clear.h"

void unsignedset_clear(struct unsignedset* this)
{
	avl_free_nodes(this->tree);
	this->len = 0;
}

