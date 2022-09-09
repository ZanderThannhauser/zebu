
#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "clear.h"

void unsignedset_clear(struct unsignedset* this)
{
	avl_free_tree(this->tree);
	this->len = 0;
}

