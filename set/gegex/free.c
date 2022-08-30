
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_gegexset(struct gegexset* this)
{
	avl_free_tree(this->tree);
	free(this);
}

