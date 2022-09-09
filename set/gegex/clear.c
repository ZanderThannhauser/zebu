
#include <debug.h>

#include <avl/free_tree.h>

#include "struct.h"
#include "clear.h"

void gegexset_clear(struct gegexset* this)
{
	avl_free_tree(this->tree);
	this->n = 0;
}

