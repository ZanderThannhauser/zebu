
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_yaccstateset(struct yaccstateset* this)
{
	avl_free_tree(this->tree);
	free(this);
}

