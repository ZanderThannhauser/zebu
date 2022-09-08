
#include <debug.h>

#include "struct.h"
#include "clear.h"

void gegexset_clear(struct gegexset* this)
{
	avl_free_nodes(this->tree);
	this->n = 0;
}

