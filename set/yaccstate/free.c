
#include <stdlib.h>

#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "free.h"

void free_yaccstateset(struct yaccstateset* this)
{
	avl_free_tree(this->tree);
	free(this);
}

